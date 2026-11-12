"use strict";

(() => {
  const $ = (id) => document.getElementById(id);
  const icons = {
    menu: '<path d="M4 6h16M4 12h16M4 18h16"/>',
    code: '<path d="m8 6-6 6 6 6m8-12 6 6-6 6M14 3l-4 18"/>',
    moon: '<path d="M20.5 13A9 9 0 0 1 11 3.5 9 9 0 1 0 20.5 13Z"/>',
    sun: '<circle cx="12" cy="12" r="4"/><path d="M12 2v2m0 16v2M2 12h2m16 0h2M5 5l1.5 1.5m11 11L19 19M5 19l1.5-1.5m11-11L19 5"/>',
    refresh: '<path d="M20 7v5h-5M4 17v-5h5"/><path d="M6 7a7 7 0 0 1 12-2l2 3M4 16l2 3a7 7 0 0 0 12-2"/>',
    search: '<circle cx="10.5" cy="10.5" r="6.5"/><path d="m16 16 5 5"/>',
    layers: '<path d="m12 3 10 5-10 5L2 8Zm-9 9 9 5 9-5M3 16l9 5 9-5"/>',
    diff: '<path d="M4 6h6M7 3v6m7-3h6M4 15h16M4 20h16"/>',
    up: '<path d="m6 14 6-6 6 6"/>',
    down: '<path d="m6 10 6 6 6-6"/>',
    box: '<path d="m12 3 9 5v9l-9 5-9-5V8Zm-9 5 9 5 9-5m-9 5v9M7.5 5.5l9 5"/>',
    pen: '<path d="m15 5 4 4M4 20l5-1L21 7a2.8 2.8 0 0 0-4-4L5 15Zm1-5 4 4"/>',
    copy: '<rect x="8" y="8" width="12" height="13" rx="2"/><path d="M15 8V5a2 2 0 0 0-2-2H5a2 2 0 0 0-2 2v8a2 2 0 0 0 2 2h3"/>',
    file: '<path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8Zm0 0v6h6M8 13h8m-8 4h6"/>',
    chevron: '<path d="m7 10 5 5 5-5"/>',
    folder: '<path d="M3 7V5a2 2 0 0 1 2-2h5l2 3h7a2 2 0 0 1 2 2v11H3Z"/>',
  };
  const icon = (name, extra = "") => `<svg ${extra} viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.6" stroke-linecap="round" stroke-linejoin="round" aria-hidden="true">${icons[name] || icons.file}</svg>`;
  document.querySelectorAll("[data-icon]").forEach((el) => { el.innerHTML = icon(el.dataset.icon); });
  const escape = (text) => String(text).replace(/[&<>"']/g, (char) => ({ "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#39;" }[char]));
  const preferences = {
    get(key, fallback) { try { return JSON.parse(localStorage.getItem(`tarjen-compare:${key}`)) ?? fallback; } catch { return fallback; } },
    set(key, value) { try { localStorage.setItem(`tarjen-compare:${key}`, JSON.stringify(value)); } catch { /* Private mode can block storage. */ } },
  };
  const data = window.TEMPLATE_DATA;
  const templates = Array.isArray(data?.templates) ? data.templates : [];
  const templateMap = new Map(templates.map((entry) => [entry.path, entry]));
  const panes = [$('full-code'), $('hand-code')];
  const state = {
    current: null, aligned: preferences.get('aligned', true), sync: preferences.get('sync', true),
    size: Math.min(20, Math.max(11, Number(preferences.get('size', 13)) || 13)),
    ratio: Math.min(75, Math.max(25, Number(preferences.get('ratio', 50)) || 50)),
    theme: preferences.get('theme', 'light'), query: '', openCategories: new Set(), diffs: [], diffIndex: -1,
  };
  const highlightCache = new Map();
  let toastTimer;
  let syncing = false;
  let selectionBeforeCopy = null;

  function toast(message) {
    $('toast').textContent = message;
    $('toast').classList.add('visible');
    clearTimeout(toastTimer);
    toastTimer = setTimeout(() => $('toast').classList.remove('visible'), 2600);
  }

  function setTheme() {
    document.documentElement.dataset.theme = state.theme;
    $('theme-button').innerHTML = icon(state.theme === 'dark' ? 'sun' : 'moon');
    $('theme-button').setAttribute('aria-label', state.theme === 'dark' ? '切换为浅色' : '切换为深色');
  }

  function setRatio(ratio) {
    state.ratio = Math.max(25, Math.min(75, ratio));
    $('comparison').style.setProperty('--left', `${state.ratio}fr`);
    $('comparison').style.setProperty('--right', `${100 - state.ratio}fr`);
    $('splitter').setAttribute('aria-valuenow', String(Math.round(state.ratio)));
  }

  function setFont() {
    document.documentElement.style.setProperty('--code-size', `${state.size}px`);
    document.documentElement.style.setProperty('--row-height', `${state.size + 10}px`);
    $('font-size').textContent = state.size;
    $('font-smaller').disabled = state.size <= 11;
    $('font-larger').disabled = state.size >= 20;
  }

  function setSidebar(open) {
    document.body.classList.toggle('sidebar-hidden', !open);
    $('menu-button').setAttribute('aria-expanded', String(open));
  }

  function sourceLines(text) {
    if (!text) return [];
    const lines = text.replace(/\r\n?/g, '\n').split('\n');
    if (lines[lines.length - 1] === '') lines.pop();
    return lines;
  }

  // Tokenize before escaping. Every source fragment is escaped before entering HTML.
  function highlightedLines(text, key) {
    if (highlightCache.has(key)) return highlightCache.get(key);
    const keyword = new Set('alignas alignof asm auto break case catch class const constexpr consteval constinit continue decltype default delete do else enum explicit export extern final for friend goto if inline mutable namespace new noexcept nullptr operator override private protected public register reinterpret_cast requires return signed sizeof static static_assert static_cast struct switch template this thread_local throw try typedef typename union unsigned using virtual volatile while co_await co_return co_yield'.split(' '));
    const types = new Set('bool char char16_t char32_t double float int long short void wchar_t size_t string vector array map set multiset unordered_map unordered_set pair tuple deque queue stack priority_queue bitset ll uint64_t int64_t'.split(' '));
    const token = /\/\*[\s\S]*?(?:\*\/|(?![\s\S]))|\/\/[^\n]*|"(?:\\[\s\S]|[^"\\])*"|'(?:\\.|[^'\\\n])*'|^[\t ]*#[^\n]*|\b\d[\w.']*\b|\b[A-Za-z_]\w*\b/gm;
    const normalized = (text || '').replace(/\r\n?/g, '\n');
    const result = [''];
    function append(fragment, type) {
      fragment.split('\n').forEach((part, index) => {
        if (index) result.push('');
        result[result.length - 1] += type && part ? `<span class="tok-${type}">${escape(part)}</span>` : escape(part);
      });
    }
    let offset = 0;
    let match;
    while ((match = token.exec(normalized))) {
      append(normalized.slice(offset, match.index));
      const value = match[0];
      let type;
      if (value.startsWith('//') || value.startsWith('/*')) type = 'comment';
      else if (/^["']/.test(value)) type = 'string';
      else if (/^\s*#/.test(value)) type = 'preprocessor';
      else if (/^\d/.test(value)) type = 'number';
      else if (keyword.has(value)) type = 'keyword';
      else if (types.has(value)) type = 'type';
      else if (/^\s*\(/.test(normalized.slice(token.lastIndex))) type = 'function';
      append(value, type);
      offset = token.lastIndex;
    }
    append(normalized.slice(offset));
    if (result[result.length - 1] === '' && normalized.endsWith('\n')) result.pop();
    highlightCache.set(key, result);
    return result;
  }

  function renderTree() {
    const query = state.query.trim().toLocaleLowerCase();
    const filtered = templates.filter((item) => `${item.path} ${item.category}`.toLocaleLowerCase().includes(query));
    const categories = ['数据结构', '图论', '字符串', '数学', '计算几何', '杂项', '赛前准备'];
    const groups = new Map();
    filtered.forEach((item) => {
      if (!groups.has(item.category)) groups.set(item.category, []);
      groups.get(item.category).push(item);
    });
    const ordered = [...groups.keys()].sort((a, b) => (categories.indexOf(a) < 0 ? 99 : categories.indexOf(a)) - (categories.indexOf(b) < 0 ? 99 : categories.indexOf(b)));
    $('result-count').textContent = query ? `找到 ${filtered.length} 份模板` : `全部 ${templates.length} 份模板`;
    $('clear-filter').hidden = !query;
    $('file-tree').innerHTML = ordered.map((category) => {
      const open = !!query || state.openCategories.has(category);
      const items = groups.get(category);
      return `<div class="tree-group"><button class="category-button ${open ? '' : 'collapsed'}" data-category="${escape(category)}" aria-expanded="${open}">${icon('chevron', 'class="chevron"')}${icon('folder')}<span>${escape(category)}</span><span class="category-count">${items.length}</span></button><div class="category-files" ${open ? '' : 'hidden'}>${items.map((item) => `<button class="file-button ${item.path === state.current?.path ? 'active' : ''}" data-path="${escape(item.path)}" title="${escape(item.path)}" ${item.path === state.current?.path ? 'aria-current="true"' : ''}>${icon('file')}<span class="file-name">${escape(item.name)}</span></button>`).join('')}</div></div>`;
    }).join('') || '<div class="no-results">没有找到匹配的模板。<br>试试文件名、算法名或分类。</div>';
  }

  function updateDiffLabel() {
    const count = state.diffs.length;
    $('diff-count').textContent = state.diffIndex < 0 ? `${count} 处差异` : `${state.diffIndex + 1} / ${count} 处差异`;
    $('previous-diff').disabled = !count;
    $('next-diff').disabled = !count;
  }

  function renderCode(keepPosition = false) {
    const current = state.current;
    if (!current) return;
    const positions = panes.map((pane) => ({ top: pane.scrollTop, left: pane.scrollLeft }));
    state.diffIndex = -1;
    state.diffs = [];
    current.rows.forEach((row, index) => {
      if (row[2] !== 'equal' && (index === 0 || current.rows[index - 1][2] === 'equal')) state.diffs.push(index);
    });
    [current.full, current.copy].forEach((source, side) => {
      const pane = panes[side];
      if (source === null) {
        pane.innerHTML = '<div class="code-message">此版本尚无对应文件。</div>';
        return;
      }
      if (!source) {
        pane.innerHTML = '<div class="code-message">此文件为空。</div>';
        return;
      }
      const highlighted = highlightedLines(source, `${current.path}:${side}`);
      const rows = state.aligned ? current.rows.map((row, index) => ({ number: row[side], tag: row[2], index })) : current.rows.flatMap((row, index) => row[side] === null ? [] : [{ number: row[side], tag: row[2], index }]);
      pane.innerHTML = rows.map(({ number, tag, index }) => {
        const status = number === null ? 'spacer' : tag === 'equal' ? '' : side === 0 ? 'removed' : 'added';
        return `<div class="code-line ${status}" data-row="${index}"><span class="line-number">${number ?? ''}</span><span class="source-text">${number === null ? ' ' : highlighted[number - 1] || ' '}</span></div>`;
      }).join('');
      pane.scrollTop = keepPosition ? positions[side].top : 0;
      pane.scrollLeft = keepPosition ? positions[side].left : 0;
    });
    $('aligned-button').classList.toggle('selected', state.aligned);
    $('raw-button').classList.toggle('selected', !state.aligned);
    $('aligned-button').setAttribute('aria-pressed', String(state.aligned));
    $('raw-button').setAttribute('aria-pressed', String(!state.aligned));
    updateDiffLabel();
  }

  function selectTemplate(path, updateURL = true) {
    const entry = templateMap.get(path);
    if (!entry) return;
    state.current = entry;
    state.openCategories.add(entry.category);
    $('file-title').textContent = entry.name;
    $('current-category').textContent = entry.category;
    $('current-path').textContent = entry.path;
    $('full-path').textContent = `src/${entry.path}`;
    $('copy-path').textContent = `src-acm/${entry.path}`;
    $('full-count').textContent = entry.full === null ? '缺少文件' : `${sourceLines(entry.full).length} 行`;
    $('copy-count').textContent = entry.copy === null ? '缺少文件' : `${sourceLines(entry.copy).length} 行`;
    $('copy-full').disabled = entry.full === null;
    $('copy-hand').disabled = entry.copy === null;
    const reduction = entry.active[0] - entry.active[1];
    $('savings').textContent = reduction > 0 ? `手抄有效代码少 ${reduction} 行 · −${Math.round(reduction / entry.active[0] * 100)}%` : '保留相同核心实现';
    document.title = `${entry.name} · 板子对照`;
    preferences.set('file', entry.path);
    if (updateURL) {
      try { history.replaceState(null, '', `#file=${encodeURIComponent(entry.path)}`); }
      catch { /* Some file:// browsers do not allow changing history. */ }
    }
    renderTree();
    renderCode();
    if (window.innerWidth <= 850) setSidebar(false);
  }

  function navigateDiff(direction) {
    if (!state.diffs.length) return;
    state.diffIndex = state.diffIndex < 0 ? direction > 0 ? 0 : state.diffs.length - 1 : (state.diffIndex + direction + state.diffs.length) % state.diffs.length;
    const rowIndex = state.diffs[state.diffIndex];
    syncing = true;
    panes.forEach((pane) => {
      pane.querySelectorAll('.current-diff').forEach((line) => line.classList.remove('current-diff'));
      const line = pane.querySelector(`[data-row="${rowIndex}"]`) || [...pane.querySelectorAll('[data-row]')].find((line) => Number(line.dataset.row) >= rowIndex) || pane.lastElementChild;
      if (line) {
        line.classList.add('current-diff');
        pane.scrollTop += line.getBoundingClientRect().top - pane.getBoundingClientRect().top - 40;
      }
    });
    requestAnimationFrame(() => { syncing = false; });
    updateDiffLabel();
  }

  async function copySource(side) {
    const text = side === 0 ? state.current?.full : state.current?.copy;
    if (text == null) return;
    try {
      if (!navigator.clipboard?.writeText) throw new Error('Use local clipboard fallback');
      await navigator.clipboard.writeText(text);
    } catch {
      const area = document.createElement('textarea');
      area.value = text;
      area.style.cssText = 'position:fixed;left:-10000px;top:0';
      area.setAttribute('readonly', '');
      document.body.append(area);
      const focused = document.activeElement;
      const selection = window.getSelection();
      selectionBeforeCopy = selection?.rangeCount ? selection.getRangeAt(0).cloneRange() : null;
      area.select();
      const copied = document.execCommand('copy');
      area.remove();
      focused?.focus({ preventScroll: true });
      if (selectionBeforeCopy && selection) { selection.removeAllRanges(); selection.addRange(selectionBeforeCopy); }
      if (!copied) { toast('复制未获浏览器允许，请选中代码后按 Ctrl+C。'); return; }
    }
    toast(`已复制${side === 0 ? '完整封装版' : '赛时手抄版'}代码`);
  }

  $('template-search').addEventListener('input', (event) => { state.query = event.target.value; renderTree(); });
  $('clear-filter').addEventListener('click', () => { state.query = ''; $('template-search').value = ''; renderTree(); $('template-search').focus(); });
  $('file-tree').addEventListener('click', (event) => {
    const file = event.target.closest('[data-path]');
    if (file) { selectTemplate(file.dataset.path); return; }
    const category = event.target.closest('[data-category]');
    if (category) {
      const name = category.dataset.category;
      if (state.query.trim()) return;
      if (state.openCategories.has(name)) state.openCategories.delete(name); else state.openCategories.add(name);
      renderTree();
    }
  });
  $('aligned-button').addEventListener('click', () => { if (!state.aligned) { state.aligned = true; preferences.set('aligned', true); renderCode(true); } });
  $('raw-button').addEventListener('click', () => { if (state.aligned) { state.aligned = false; preferences.set('aligned', false); renderCode(true); } });
  $('sync-scroll').checked = state.sync;
  $('sync-scroll').addEventListener('change', (event) => { state.sync = event.target.checked; preferences.set('sync', state.sync); });
  panes.forEach((pane, index) => {
    pane.addEventListener('scroll', () => {
      if (!state.sync || syncing) return;
      syncing = true;
      const other = panes[1 - index];
      other.scrollTop = state.aligned ? pane.scrollTop : pane.scrollTop / Math.max(1, pane.scrollHeight - pane.clientHeight) * (other.scrollHeight - other.clientHeight);
      other.scrollLeft = pane.scrollLeft;
      requestAnimationFrame(() => { syncing = false; });
    }, { passive: true });
  });
  $('copy-full').addEventListener('click', () => copySource(0));
  $('copy-hand').addEventListener('click', () => copySource(1));
  $('previous-diff').addEventListener('click', () => navigateDiff(-1));
  $('next-diff').addEventListener('click', () => navigateDiff(1));
  $('font-smaller').addEventListener('click', () => { state.size = Math.max(11, state.size - 1); preferences.set('size', state.size); setFont(); });
  $('font-larger').addEventListener('click', () => { state.size = Math.min(20, state.size + 1); preferences.set('size', state.size); setFont(); });
  $('theme-button').addEventListener('click', () => { state.theme = state.theme === 'light' ? 'dark' : 'light'; preferences.set('theme', state.theme); setTheme(); });
  $('refresh-button').addEventListener('click', () => location.reload());
  $('menu-button').addEventListener('click', () => setSidebar(document.body.classList.contains('sidebar-hidden')));
  $('sidebar-scrim').addEventListener('click', () => setSidebar(false));
  $('splitter').addEventListener('pointerdown', (event) => {
    if (event.button !== 0) return;
    event.preventDefault();
    $('splitter').setPointerCapture(event.pointerId);
    document.body.classList.add('resizing');
  });
  $('splitter').addEventListener('pointermove', (event) => {
    if (!$('splitter').hasPointerCapture(event.pointerId)) return;
    const rect = $('comparison').getBoundingClientRect();
    setRatio((event.clientX - rect.left) / rect.width * 100);
  });
  function endResize() { document.body.classList.remove('resizing'); preferences.set('ratio', state.ratio); }
  $('splitter').addEventListener('pointerup', endResize);
  $('splitter').addEventListener('pointercancel', endResize);
  $('splitter').addEventListener('lostpointercapture', endResize);
  $('splitter').addEventListener('dblclick', () => { setRatio(50); preferences.set('ratio', 50); });
  $('splitter').addEventListener('keydown', (event) => {
    if (event.key === 'ArrowLeft' || event.key === 'ArrowRight') {
      event.preventDefault(); setRatio(state.ratio + (event.key === 'ArrowLeft' ? -2 : 2)); preferences.set('ratio', state.ratio);
    } else if (event.key === 'Home') { event.preventDefault(); setRatio(50); preferences.set('ratio', 50); }
  });
  document.addEventListener('keydown', (event) => {
    if (event.altKey && ['ArrowUp', 'ArrowDown'].includes(event.key)) { event.preventDefault(); navigateDiff(event.key === 'ArrowDown' ? 1 : -1); }
    if (event.key === '/' && !event.ctrlKey && !event.metaKey && !['INPUT', 'TEXTAREA'].includes(document.activeElement.tagName)) { event.preventDefault(); setSidebar(true); $('template-search').focus(); }
    if (event.key === 'Escape') {
      if (state.query) { state.query = ''; $('template-search').value = ''; renderTree(); }
      if (window.innerWidth <= 850) setSidebar(false);
    }
  });
  window.addEventListener('hashchange', () => {
    const path = new URLSearchParams(location.hash.slice(1)).get('file');
    if (path && path !== state.current?.path) selectTemplate(path, false);
  });

  setTheme();
  setFont();
  setRatio(state.ratio);
  setSidebar(window.innerWidth > 850);
  $('template-total').textContent = templates.length;
  if (templates.length) {
    const generated = new Date(data.generatedAt);
    $('snapshot-time').textContent = `快照 ${generated.toLocaleString('zh-CN', { month: '2-digit', day: '2-digit', hour: '2-digit', minute: '2-digit', hour12: false })}`;
    $('snapshot-time').title = '代码修改后重新运行「查看模板对照.bat」更新快照';
    const requested = new URLSearchParams(location.hash.slice(1)).get('file');
    const saved = preferences.get('file', 'data_structure/SegmentTree.cpp');
    selectTemplate(templateMap.has(requested) ? requested : templateMap.has(saved) ? saved : templates[0].path);
  } else {
    $('empty-state').hidden = false;
    $('file-title').textContent = '尚未生成模板快照';
    renderTree();
    ['copy-full', 'copy-hand', 'next-diff', 'previous-diff', 'aligned-button', 'raw-button'].forEach((id) => { $(id).disabled = true; });
  }
})();

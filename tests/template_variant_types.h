#pragma once

#if defined(ACM_VARIANT) || defined(HANDCOPY_FIXED_TYPES)
#define CP_TEST_TYPE(Name, ...) Name
using TemplateTestValue = long long;
#else
#define CP_TEST_TYPE(Name, ...) Name<__VA_ARGS__>
using TemplateTestValue = int;
#endif

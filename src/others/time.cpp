struct gettime {
    clock_t star, ends;
    gettime() { star = clock(); }
    ~gettime() {
        ends = clock();
        cout << "Running Time : " << (double)(ends - star) / CLOCKS_PER_SEC
             << endl;
    }
} tim;
int main() {
    tim.begin();
    tim.end();
    return 0;
}
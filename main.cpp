#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;


class Num_Row {
private:
    list<long> row;
public:
    void add_num(long val) {
        row.push_back(val);
    }

    bool is_all_zeros() {
        bool all_zeroes = true;
        for (list<long>::iterator currNum = row.begin(); currNum != row.end(); currNum++) {
            if (*currNum != 0) {
                all_zeroes = false;
            }
        }
        return all_zeroes;
    }

    long get_last() {
        if (is_all_zeros()) {
            return 0;
        }
        else {
            list<long>::iterator nextNum = row.begin();
            nextNum++;
            Num_Row row_below;
            for (list<long>::iterator currNum = row.begin(); nextNum != row.end(); currNum++, nextNum++) {
                long val = (*nextNum) - (*currNum);
                row_below.add_num(val);
            }
            long below_last = row_below.get_last();
            list<long>::reverse_iterator last = row.rbegin();
            return (*last) + below_last;
        }
    }

    long get_new_first() {
        if (is_all_zeros()) {
            return 0;
        }
        else {
            list<long>::iterator nextNum = row.begin();
            nextNum++;
            Num_Row row_below;
            for (list<long>::iterator currNum = row.begin(); nextNum != row.end(); currNum++, nextNum++) {
                long val = (*nextNum) - (*currNum);
                row_below.add_num(val);
            }
            long below_first = row_below.get_new_first();
            nextNum = row.begin();
            return (*nextNum) - below_first;
        }
    }
};

bool isNum(char c) {
    return ('0' <= c && c <= '9');
}

long toNum(char c) {
    return (c - '0');
}

void create_row(string line, Num_Row &row) {
    for (int pos = 0; pos < line.length(); pos++) {
        bool negative = false;
        if (line[pos] == '-') {
            negative = true;
            pos++;
        }
        long val=0;
        while (isNum(line[pos])) {
            if (negative) {
                val = (val*10) - toNum(line[pos]);
            }
            else {
                val = (val*10) + toNum(line[pos]);
            }
            pos++;
        }
        row.add_num(val);
    }
}

int main(int argc, char **argv) {
    ifstream input_file;
    input_file.open("input.txt");
    string line;


    // Part 1

    long last_sum = 0;

    while (getline(input_file, line)) {
        Num_Row row;
        create_row(line, row);
        last_sum += row.get_last();
    }
    input_file.close();

    cout << "Part 1: Sum of values = " << last_sum << endl;

    // Part 2

    input_file.open("input.txt");

    long first_sum = 0;

    while (getline(input_file, line)) {
        Num_Row row;
        create_row(line, row);
        first_sum += row.get_new_first();
    }
    input_file.close();

    cout << "Part 2: Sum of values = " << first_sum << endl;

    return 0;
}

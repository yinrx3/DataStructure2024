#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>

using namespace std;

// 定义子句类型
using Clause = vector<int>;
using Formula = vector<Clause>;

// 定义状态类型
struct State {
    Formula clauses;
    bool assignment[100];  // 假设变量的数量不超过 100
    bool assigned[100];   // 记录哪些变量已经赋值
};

// 单元传播函数
void unit_propagation(Formula& clauses, bool assignment[], bool assigned[]) {
    queue<int> unit_queue;

    for (const auto& clause : clauses) {
        if (clause.size() == 1) {
            unit_queue.push(clause[0]);
        }
    }

    while (!unit_queue.empty()) {
        int unit_literal = unit_queue.front();
        unit_queue.pop();
        int var = abs(unit_literal);
        assignment[var] = (unit_literal > 0);
        assigned[var] = true;

        for (auto it = clauses.begin(); it != clauses.end();) {
            auto& clause = *it;
            bool clause_contains_literal = false;

            for (auto lit_it = clause.begin(); lit_it != clause.end();) {
                if (*lit_it == unit_literal) {
                    it = clauses.erase(it);
                    clause_contains_literal = true;
                    break;
                } else if (*lit_it == -unit_literal) {
                    lit_it = clause.erase(lit_it);
                    if (clause.size() == 1) {
                        unit_queue.push(clause[0]);
                    }
                } else {
                    ++lit_it;
                }
            }
            if (!clause_contains_literal) {
                ++it;
            }
        }
    }
}

// 纯文字消去函数
void pure_literal_elimination(Formula& clauses, bool assignment[], bool assigned[]) {
    bool pure_literals[100] = {false};  // 记录每个变量是否为纯文字

    for (const auto& clause : clauses) {
        for (int literal : clause) {
            int var = abs(literal);
            if (!assigned[var]) {
                pure_literals[var] = (pure_literals[var] || (literal > 0));
            }
        }
    }

    for (int i = 1; i < 100; ++i) {
        if (!assigned[i] && pure_literals[i]) {
            assignment[i] = true;
            assigned[i] = true;
            for (auto it = clauses.begin(); it != clauses.end();) {
                if (find(it->begin(), it->end(), i) != it->end() ||
                    find(it->begin(), it->end(), -i) != it->end()) {
                    it = clauses.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }
}

// 选择未赋值的变量
int choose_literal(const Formula& clauses, bool assigned[], int var_count) {
    for (int i = 1; i <= var_count; ++i) {
        if (!assigned[i]) {
            return i;
        }
    }
    return 0;  // 没有未赋值的变量
}

// DPLL 算法
bool dpll(Formula clauses, bool assignment[], bool assigned[], int var_count) {
    stack<State> state_stack;
    state_stack.push({clauses, assignment, assigned});

    while (!state_stack.empty()) {
        State current_state = state_stack.top();
        state_stack.pop();

        unit_propagation(current_state.clauses, current_state.assignment, current_state.assigned);
        pure_literal_elimination(current_state.clauses, current_state.assignment, current_state.assigned);

        if (current_state.clauses.empty()) {
            return true;  // 所有子句都被满足
        }

        bool all_clauses_satisfied = true;

        for (const auto& clause : current_state.clauses) {
            if (!clause.empty()) {
                all_clauses_satisfied = false;
                break;
            }
        }
        if (all_clauses_satisfied) {
            return true;  // 所有子句都被满足
        }

        int literal = choose_literal(current_state.clauses, current_state.assigned, var_count);
        if (literal != 0) {
            State new_state = current_state;
            new_state.assignment[literal] = true;
            new_state.assigned[literal] = true;

            state_stack.push(current_state);  // 回溯状态
            state_stack.push(new_state);  // 推入新的状态
        }
    }

    return false;
}

int main() {
    // 示例子句
    Formula clauses = {
        {1, 2, -3},
        {-1, 2, 3},
        {-2, -3, 4},
        {3, -4, 5}
    };

    bool assignment[100] = {false};  // 初始化所有变量的赋值为 false
    bool assigned[100] = {false};    // 初始化所有变量的赋值状态为 false
    int var_count = 5;  // 变量的数量

    if (dpll(clauses, assignment, assigned, var_count)) {
        cout << "Satisfiable" << endl;
        for (int i = 1; i <= var_count; ++i) {
            if (assigned[i]) {
                cout << i << " = " << assignment[i] << endl;
            }
        }
    } else {
        cout << "Unsatisfiable" << endl;
    }

    return 0;
}
#include <vector>
#include <iostream>
#include <chrono>

#define max_val 1
#define min_val -1
#define TIKUT 33

int minimax_val_max[TIKUT] = {};
int minimax_val_min[TIKUT] = {};

// siirtogeneraattori
std::vector<int> get_legal_moves(int n)
{
    std::vector<int> retval;
    for (int i = 1; (i <= n) && (i <= 3); ++i)
        retval.push_back(i);

    return retval;
}

// pelipuuhaku
int minimax_tree(int const n, bool const max)
{
    if (n == 0)
        return max ? max_val : min_val;
    if (n == 1)
        return max ? min_val : max_val;

    if (max && minimax_val_max[n - 1])
        return minimax_val_max[n - 1];
    if (!max && minimax_val_min[n - 1])
        return minimax_val_min[n - 1];

    std::vector<int> mv = get_legal_moves(n); /* get legal moves palauttaa vektorin laillisista siirroista, esim. 1,2,3 */
    int best_val;
    if (max) {
        best_val = min_val;
        for (int const lm : mv) {
            int const val = minimax_tree(n - lm, false);
            if (val > best_val)
                best_val = val;
        }
    }
    else { // min
        best_val = max_val;
        for (int const lm : mv) {
            int const val = minimax_tree(n - lm, true);
            if (val < best_val)
                best_val = val;
        }
    }

    if (max)
        minimax_val_max[n - 1] = best_val;
    else
        minimax_val_min[n - 1] = best_val;

    return best_val;
}

// pelipuuhaku
int minimax(int const n, bool const max)
{
    std::vector<int> mv = get_legal_moves(n); /* get legal moves palauttaa vektorin laillisista siirroista, esim. 1,2,3 */
    int best_val;
    if (max) {
        best_val = min_val;
        for (int const lm : mv) {
            int const val = minimax(n - lm, false);
            if (val > best_val)
                best_val = val;
        }
    }
    else { // min
        best_val = max_val;
        for (int const lm : mv) {
            int const val = minimax(n - lm, true);
            if (val < best_val)
                best_val = val;
        }
    }
    return best_val;
}

int alphabeta(int const n, int a, int b, bool const max)
{
    if (n == 0)
        return max ? max_val : min_val;
    if (n == 1)
        return max ? min_val : max_val;

    std::vector<int> mv = get_legal_moves(n); /* get legal moves palauttaa vektorin laillisista siirroista, esim. 1,2,3 */
    int best_val;
    if (max) {
        best_val = min_val;
        for (int const lm : mv) {
            int const val = alphabeta(n - lm, a, b, false);
            if (val > best_val)
                best_val = val;
            if (best_val > b)
                break;
            a = std::max(a, best_val);
        }
    }
    else { // min
        best_val = max_val;
        for (int const lm : mv) {
            int const val = alphabeta(n - lm, a, b, true);
            if (val < best_val)
                best_val = val;
            if (best_val < a)
                break;
            b = std::min(b, best_val);
        }
    }
    return best_val;
}

int alphabeta_tree(int const n, int a, int b, bool const max)
{
    if (n == 0)
        return max ? max_val : min_val;
    if (n == 1)
        return max ? min_val : max_val;

    if (max && minimax_val_max[n - 1])
        return minimax_val_max[n - 1];
    if (!max && minimax_val_min[n - 1])
        return minimax_val_min[n - 1];

    std::vector<int> mv = get_legal_moves(n); /* get legal moves palauttaa vektorin laillisista siirroista, esim. 1,2,3 */
    int best_val;
    if (max) {
        best_val = min_val;
        for (int const lm : mv) {
            int const val = alphabeta_tree(n - lm, a, b, false);
            if (val > best_val)
                best_val = val;
            if (best_val > b)
                break;
            a = std::max(a, best_val);
        }
    }
    else { // min
        best_val = max_val;
        for (int const lm : mv) {
            int const val = alphabeta_tree(n - lm, a, b, true);
            if (val < best_val)
                best_val = val;
            if (best_val < a)
                break;
            b = std::min(b, best_val);
        }
    }

    if (max)
        minimax_val_max[n - 1] = best_val;
    else
        minimax_val_min[n - 1] = best_val;


    return best_val;
}


int main()
{
    // Minimax
    auto m_start = std::chrono::high_resolution_clock::now();
    bool m_score = minimax(TIKUT, true);
    auto m_stop = std::chrono::high_resolution_clock::now();
    auto m_dur = std::chrono::duration_cast<std::chrono::milliseconds>(m_stop - m_start);
    std::cout << "Minimax value: " << m_score << "(" << m_dur.count() << "ms)" << std::endl;

    // AlphaBeta
    auto ab_start = std::chrono::high_resolution_clock::now();
    bool ab_score = alphabeta(TIKUT, -1, 1, true);
    auto ab_stop = std::chrono::high_resolution_clock::now();
    auto ab_dur = std::chrono::duration_cast<std::chrono::milliseconds>(ab_stop - ab_start);
    std::cout << "AlphaBeta value: " << ab_score << "(" << ab_dur.count() << "ms)" << std::endl;


    // Minimax with search table
    auto mt_start = std::chrono::high_resolution_clock::now();
    bool mt_score = minimax_tree(TIKUT, true);
    auto mt_stop = std::chrono::high_resolution_clock::now();
    auto mt_dur = std::chrono::duration_cast<std::chrono::microseconds>(mt_stop - mt_start);
    std::cout << "Minimax with tree value: " << mt_score << "(" << mt_dur.count() << "mcs)" << std::endl;

    // AlphaBeta with search table
    auto abt_start = std::chrono::high_resolution_clock::now();
    bool abt_score = alphabeta_tree(TIKUT, -1, 1, true);
    auto abt_stop = std::chrono::high_resolution_clock::now();
    auto abt_dur = std::chrono::duration_cast<std::chrono::microseconds>(abt_stop - abt_start);
    std::cout << "AlphaBeta with tree value: " << abt_score << "(" << abt_dur.count() << "mcs)" << std::endl;


    return 0;
}
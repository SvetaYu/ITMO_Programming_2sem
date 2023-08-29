//#include "algorithms.h"

template<typename iterator, typename predicate, typename parameter>
bool all_of(iterator start, iterator end, predicate pred(parameter param)) {
    for (; start != end; ++start) {
        if (!pred(*start)) {
            return false;
        }
    }
    return true;
}

template<typename iterator, typename predicate, typename parameter>
bool any_of(iterator start, iterator end, predicate pred(parameter param)) {
    for (; start != end; ++start) {
        if (pred(*start)) {
            return true;
        }
    }
    return false;
}

template<typename iterator, typename predicate, typename parameter>
bool none_of(iterator start, iterator end, predicate pred(parameter param)) {
    for (; start != end; ++start) {
        if (pred(*start)) {
            return false;
        }
    }
    return true;
}

template<typename iterator, typename predicate, typename parameter>
bool one_of(iterator start, iterator end, predicate pred(parameter param)) {
    bool check = false;
    for (; start != end; ++start) {
        if (pred(*start)) {
            if (check) {
                return false;
            }
            check = true;
        }
    }
    if (check) {
        return true;
    }
    return false;
}

template<typename iterator, typename predicate, typename parameter>
bool is_sorted(iterator start, iterator end, predicate pred(parameter left, parameter right)) {
    for (; start != end - 1; ++start) {
        if (!pred(*start, *(start + 1))) {
            return false;
        }
    }
    return true;
}

template<typename iterator, typename predicate, typename parameter>
bool is_partitioned(iterator start, iterator end, predicate pred(parameter param)) {
    while (pred(*start) && start != end) {
        ++start;
    }
    while (start != end) {
        if (pred(*start)) {
            return false;
        }
        ++start;
    }
    return true;
}

template<typename iterator, typename type>
iterator find_not(iterator start, iterator end, type value) {
    for (; start != end; ++start) {
        if (*start != value) {
            return start;
        }
    }
    return end;
}

template<typename iterator, typename type>
iterator find_backward(iterator start, iterator end, type value) {
    for (--end; start-1 != end; --end) {
        if (*end == value) {
            return end;
        }
    }
    return end;
}

template<typename iterator>
bool is_palindrome(iterator start, iterator end) {
    --end;
    while (start < end) {
        if (*start != *end) {
            return false;
        }
        ++start;
        --end;
    }
    return true;
}
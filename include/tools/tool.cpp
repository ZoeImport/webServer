#include <functional>
#include <utility>
template <typename F, typename... Args>
auto wrapFunc(F &&f, Args &&...args) {
    return std::bind(std::forward<F>(f), std::forward<Args>(args)...);
}
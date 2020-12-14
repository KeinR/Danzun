

template<typename T>
dan::LuaRef<T>::LuaRef(sol::userdata ref): ref(ref), ptr(ref.as<T*>()) {
}
template<typename T>
T &dan::LuaRef<T>::operator*() {
    return *ptr;
}
template<typename T>
T *dan::LuaRef<T>::operator->() {
    return ptr;
}


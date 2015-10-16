#ifndef __FLEXUS_WHATEVER_HPP__
#define __FLEXUS_WHATEVER_HPP__

#include <typeinfo>

namespace flx
{
    class Whatever
    {
    private:
        /* static cast */
        template<typename T>
        T& stat()
        {
            return static_cast<Data<T>&>(*ptr).get();
        }

        /* const static cast */
        template<typename T>
        const T& stat() const
        {
            return static_cast<Data<T> const&>(*ptr).get();
        }

        /* dynamic cast */
        template<typename T>
        T& dyn()
        {
            return dynamic_cast<Data<T>&>(*ptr).get();
        }

        /* const dynamic cast */
        template<typename T>
        const T& dyn() const
        {
            return dynamic_cast<Data<T> const&>(*ptr).get();
        }

        /* abstract Base class */
        struct Base
        {
            virtual ~Base() {} // virtual destructor
            virtual size_t getType() const = 0; // virtual type check
            virtual Base* copy() const = 0; // virtual copy method
        } *ptr = nullptr;

        /* derived Base class Data */
        template<typename T>
        struct Data : public Base
        {
        private:
            T data; // data is stored here

        public:

            /* constructor */
            Data(const T &d):
                data(d)
            {

            }

            /* return data */
            T& get()
            {
                return data;
            }

            /* return const data */
            const T& get() const
            {
                return data;
            }

            /* override virtual copy method */
            Base* copy() const override
            {
                return new Data(get());
            }

            size_t getType() const override
            {
                return typeid(T).hash_code();
            }

        };

    public:

        /* default constructor */
        Whatever()
        {

        }

        /* constructor */
        template<typename T>
        Whatever(const T &w):
            ptr(new Data<T>(w))
        {

        }

        /* copy constructor */
        Whatever(const Whatever &w) : ptr(w.ptr->copy())
        {

        }

        /* move constructor */
        Whatever(Whatever &&w) : ptr(w.ptr)
        {
            w.ptr = nullptr;
        }

        /* destructor */
        ~Whatever()
        {
            delete ptr;
        }

        /* assign operator */
        Whatever& operator=(Whatever w)
        {
            swap(*this, w);
            return *this;
        }

        /* swap */
        friend void swap(Whatever &w1, Whatever &w2)
        {
            std::swap(w1.ptr, w2.ptr);
        }

        /* clear */
        void clear()
        {
            delete ptr;
            ptr = nullptr;
        }

        /* empty */
        bool empty() const
        {
            return ptr;
        }

        /* typecheck */
        template<typename T>
        bool is() const
        {
            return typeid(T).hash_code() == ptr->getType();
        }

        /* static cast */
        template<typename T>
        T&& get() &&
        {
            return std::move(stat<T>());
        }

        template<typename T>
        T& get() &
        {
            return stat<T>();
        }

        template<typename T>
        const T& get() const &
        {
            return stat<T>();
        }

        /* dynamic cast */
        template<typename T>
        T&& cast() &&
        {
            return std::move(dyn<T>());
        }

        template<typename T>
        T& cast() &
        {
            return dyn<T>();
        }

        template<typename T>
        const T& cast() const &
        {
            return dyn<T>();
        }

        /* what the heck is that? */
        /* TODO ask Phil what method () is */
        template<typename T>
        operator T&& () &&
        {
            return std::move(get<T>());
        }

        template<typename T>
        operator T& () &
        {
            return get<T>();
        }

        template<typename T>
        operator const T& () const &
        {
            return get<T>();
        }
    };
}

#endif // __FLEXUS_WHATEVER_HPP__

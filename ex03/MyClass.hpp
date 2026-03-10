#ifndef MYCLASS_HPP
# define MYCLASS_HPP

class MyClass
{
    public:
        MyClass( void );
        MyClass( MyClass const & src );
        ~MyClass( void );

        MyClass & operator=( MyClass const & rhs );

    private:
};

#endif

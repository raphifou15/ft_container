# include "iterator.hpp"

namespace ft
{
    template<class Iterator>
    class bidirectional_iterator : public bidirectional_iterator_tag, Iterator>
    {
        
    };
}
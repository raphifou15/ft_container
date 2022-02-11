#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iostream>
# include <stdexcept>
# include <sstream>
# include "lexicographical_compare.hpp"
# include "iterator.hpp"
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		private:
			Allocator	_alloc;
			T			*_memory; // la ou on assigne toute la memoire.
			typename Allocator::size_type	_size; // taille du nombre d'element a l'interieur du vector.
			typename Allocator::size_type	_capacity; // combien on peut mettre d'element dans le vector sans reallouer de la memoire.
			/*
				function
			*/
			void	reallocateNumberOfCopy(typename Allocator::size_type n)
			{
				// creer un nouvel espace memoire de taille n;
				// copier les donnees dans ce nouvel espace memoire;
				// 
				T	*newMemory;

				newMemory = this->_alloc.allocate(n);
				for (typename Allocator::size_type i = 0; i < this->_size; i++)
				{
					this->_alloc.construct(&newMemory[i], this->_memory[i]);
					this->_alloc.destroy(&this->_memory[i]);
				}
				this->_alloc.deallocate(this->_memory, this->_capacity);
				this->_memory = newMemory;
				this->_capacity = n;
			}
		public:
			// types:
			typedef typename Allocator::reference				reference;
			typedef typename Allocator::const_reference 		const_reference;
			typedef	ft::random_access_iterator<T>      			iterator; // See 23.1
			typedef ft::random_access_iterator<const T>			const_iterator; // See 23.1
			typedef typename Allocator::size_type				size_type; // See 23.1
			typedef typename Allocator::difference_type			difference_type;// See 23.1 The signed integer type describes an object that can represent the difference between the addresses of any two elements in a sequence that an object of template class allocator can allocate
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename Allocator::pointer					pointer;
			typedef typename Allocator::const_pointer			const_pointer;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			// 23.2.4.1 construct/copy/destroy:
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
			explicit vector(const Allocator& = Allocator()) : _memory(NULL), _size(0), _capacity(0) 
			{
				//std::cout << "memory allocated?" << std::endl;
				this->_memory = this->_alloc.allocate(_capacity);
			}
        
			explicit vector(size_type n, const T & lala = T(),const Allocator&  = Allocator()) : _memory(NULL), _size(n), _capacity(n)
			{
				this->_memory = this->_alloc.allocate(_capacity);
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(&this->_memory[i], lala);
			}
			
		
			template<class InputIterator>
			vector( InputIterator first, InputIterator last, const Allocator& = Allocator(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) : _memory(NULL), _size(0), _capacity(0)
			{
				int i = 0;
				InputIterator lala;
				lala = first;
				for (;first != last; first++)
					i++;
				this->_size = i;
				this->_capacity = i;
				this->_memory = this->_alloc.allocate(i);
				first = lala;
				for (int i = 0; first != last; first++, i++)
					this->_alloc.construct(&this->_memory[i], *first);
			}
		
			vector(const vector<T,Allocator>& x) : _memory(NULL), _size(x._size), _capacity(x._size)
			{
				this->_memory = this->_alloc.allocate(this->_capacity);
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(&this->_memory[i], x._memory[i]);
			}
			~vector()
			{
				for (size_t i = 0; i < this->_size; i++)
					this->_alloc.destroy(&this->_memory[i]);
				this->_alloc.deallocate(this->_memory, this->_capacity);
			}
        
			vector<T,Allocator>& operator=(const vector<T,Allocator>& x)
			{
				this->clear();
				this->_alloc.deallocate(this->_memory, this->_capacity);
				this->_memory = NULL;
				this->_size = x._size;
				this->_capacity = (this->_capacity >= x._capacity) ? this->_capacity + 0 : x._capacity;
				this->_alloc = x._alloc;
				this->_memory = this->_alloc.allocate(this->_capacity);
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(&this->_memory[i], x._memory[i]);
				return *this;
			}
		
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last)
			{
				this->erase(this->begin(), this->end());
				this->insert(this->begin(), first, last);
			}
		
			void assign(size_type n, const T& u)
			{
				erase(this->begin(), this->end());
				insert(this->begin(), n, u);
			}

			allocator_type get_allocator() const
			{
				return this->_alloc;
			}
		
		
			// iterators:
		
        
			iterator				begin()
			{
				return (iterator(this->_memory));
			}
			
			const_iterator			begin() const
			{
				return (const_iterator(this->_memory));
			}

			iterator				end()
			{
				value_type	*lala = this->_memory;
				lala += this->_size;
				return (iterator(lala));
			}

			const_iterator			end() const
			{
				value_type	*lala = this->_memory;
				lala += this->_size;
				return (const_iterator(lala));
			}

			reverse_iterator		rbegin()
			{
				return reverse_iterator(end());
			}

			const_reverse_iterator 	rbegin() const
			{
				return reverse_iterator(end());
			}

			reverse_iterator 		rend()
			{
				return reverse_iterator(begin());
			}

			const_reverse_iterator 	rend() const
			{
				return reverse_iterator(begin());
			}


		// 23.2.4.2 capacity: normalement finnis
			size_type				size() const
			{
				return this->_size;
			}
			size_type				max_size() const
			{
				return this->_alloc.max_size();
			}
			void					resize(size_type sz, T c = T())
			{
				if (sz < this->size())
				{
					for (; sz < this->_size ; this->_size--)
					{
						this->_alloc.destroy(&this->_memory[this->_size - 1]);
					}
				}
				if (sz > this->size())
				{
					if ((sz > this->_capacity) && sz < (this->_capacity * 2))
					{
							this->reserve(this->_capacity * 2);
					}
					else if (sz > this->_capacity)
					{
						this->reserve(sz);
					}
					for (; this->_size < sz; this->_size++)
						this->_alloc.construct(&this->_memory[this->_size], c);
				}
			}
			size_type				capacity() const
			{
				return this->_capacity;
			}
			bool					empty() const
			{
				return (this->_size > 0) ? 0 : 1;
			}
			void					reserve(size_type n)
			{
				if (n > this->max_size())
					throw std::length_error("vector::reserve");
				else if(this->_capacity < n)
				{
						this->reallocateNumberOfCopy(n);
				}
				// Reallouer la memoire pour n capaciter si n est superieur a n capaciter.
				// Le but de cette fomction est de permettre de faire.
			}

		// element access:
			reference				operator[](size_type n)
			{
				return (*(this->_memory + n));
			}
			const_reference			operator[](size_type n) const
			{
				return (*(this->_memory + n));
			}
			const_reference			at(size_type n) const
			{
				if (this->_size <= n)
				{
					std::string lala;
					std::ostringstream convert;
					std::ostringstream convert2;
					lala = "vector::_M_range_check: __n (which is ";
					convert << n;
					lala += (convert.str() + ") >= this->size() (which is ");
					convert2 << this->_size;
					lala += (convert2.str() + ")");
					throw std::out_of_range(lala);
				}
				else
					return (this->_memory[n]);
			}
			reference				at(size_type n)
			{
				if (this->_size <= n)
				{
					std::string lala;
					std::ostringstream convert;
					std::ostringstream convert2;
					lala = "vector::_M_range_check: __n (which is ";
					convert << n;
					lala += (convert.str() + ") >= this->size() (which is ");
					convert2 << this->_size;
					lala += (convert2.str() + ")");
					throw std::out_of_range(lala);
				}
				else
					return (this->_memory[n]);
			}
			reference				front()
			{
			 	return (*(this->_memory));
			 //appeler cette fonction sur un vector vide cause des comportements indefinis.
			}

			const_reference			front() const
			{
				return (*(this->_memory));
			 	//appeler cette fonction sur un vector vide cause des comportements indefinis.
			}
			reference				back()
			{
				return (*(this->_memory + this->_size - 1));
				//appeler cette fonction sur un vector vide cause des comportements indefinis.
			}
			const_reference			back() const
			{
				return (this->_memory[this->_size - 1]);
				//appeler cette fonction sur un vector vide cause des comportements indefinis.
			}
        
		// 23.2.4.3 modifiers:

			void					push_back(const T& x)
			{
				if (this->_size == this->_capacity)
				{
					if (this->_capacity == 0)
						this->reserve(1);
					else
						this->reserve(this->_capacity * 2);
				}
				this->_alloc.construct(&this->_memory[this->_size], x);
				this->_size++;
			}
		
			void					pop_back()
			{
				this->_alloc.destroy(&this->_memory[this->_size - 1]);
				this->_size--;
			}
		
			iterator				insert(iterator position, const T& x)
			{
				size_type range1 = 0;
				for(iterator it = this->begin(); it != position; it++)
					range1++;
				insert(position, 1, x);
				iterator it = this->begin();
				for(; range1 != 0; it++)
					range1--;
				return (it);
			}
			
			void					insert(iterator position, size_type n, const T& x)
			{
				if (n <= 0)
					return ;
				size_type range1 = 0;
				size_type range2 = this->size();
				for (iterator it = this->begin(); it != position; it++)
					range1++;
				if (this->_capacity <= (this->_size + n))
				{
					if ((this->_size * 2) > this->max_size())
						reserve(this->max_size());
					else if ((this->_size * 2) < (this->_size + n))
						reserve(n + this->size());
					else
						reserve(this->_size * 2);
				}
				for (; range2 > range1; range2--)
				{
					this->_alloc.construct(&this->_memory[range2 - 1 + n], this->_memory[range2 - 1]);
					this->_alloc.destroy(&this->_memory[range2 - 1]);
				}
				for (size_type n2 = 0; n2 < n ; n2++)
				{
					this->_alloc.construct(&this->_memory[range2 - 1 + n], x);
					range2--;
				}
				this->_size += n;
			}
			
		
			template <class InputIterator>
			void					insert(iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				size_type range1 = 0;
				size_type range2 = this->size();
				size_type n = 0;
				for (iterator it = this->begin(); it != position; it++)
					range1++;
				for (InputIterator ite = first; ite != last; ite++)
					n++;
				if (this->_capacity <= (this->_size + n))
				{
					if ((this->_size * 2) > this->max_size())
						reserve(this->max_size());
					else if ((this->_size * 2) < (this->_size + n))
						reserve(n + this->size());
					else
						reserve(this->_size * 2);
				}
				for (; range2 > range1; range2--)
				{
					this->_alloc.construct(&this->_memory[range2 - 1 + n], this->_memory[range2 - 1]);
					this->_alloc.destroy(&this->_memory[range2 - 1]);
				}
				for (size_type n2 = 0; n2 < n ; n2++)
				{
					this->_alloc.construct(&this->_memory[range2 - 1 + n], *(--last));
					range2--;
				}
				this->_size += n;
			}
			
			iterator				erase(iterator position)
			{
				size_type range1 = 0;
				size_type target = 0;

				for (iterator it = this->begin(); it != position; it++)
					range1++;
				target = range1;

				for (; range1 < this->size(); range1++)
				{
					this->_alloc.destroy(&this->_memory[range1]);
					if (range1 < (this->size() - 1))
						this->_alloc.construct(&this->_memory[range1], *(this->_memory + range1 + 1));
				}
				if (target < this->_size)
					this->_size--;
				return (position);
			}

			iterator				erase(iterator first, iterator last)
			{
				size_type range1 = 0;
				size_type n = 0;
				size_type target;
				for (iterator it = this->begin(); it != first; it++)
					range1++;
				for (iterator ite = first; ite != last; ite++)
					n++;
				target = range1;
				for (size_type range2 = range1; (range2 < (range1 + n) && (range2 < this->_size)); range2++)
					this->_alloc.destroy(&this->_memory[range2]);
				for (; range1 < (this->size()); range1++)
				{
					if (n != 0)
					{
						if (this->size() > (range1 + n))
						{
							this->_alloc.construct(&this->_memory[range1], this->_memory[range1 + n]);
							this->_alloc.destroy(&this->_memory[range1 + n]);
						}
					}
				}
				if (target < this->_size)
					this->_size -= n;
				return (first);
			}

			void					swap(vector<T,Allocator>& x)
			{
				allocator_type	tmp_alloc;
				value_type		*tmp_memory; 
				size_type		tmp_size;
				size_type		tmp_capacity;

				tmp_alloc = this->_alloc;
				tmp_memory = this->_memory;
				tmp_size = this->_size;
				tmp_capacity = this->_capacity;

				this->_alloc = x._alloc;
				this->_memory = x._memory;
				this->_size = x._size;
				this->_capacity = x._capacity;

				x._alloc = tmp_alloc;
				x._memory = tmp_memory;
				x._size = tmp_size;
				x._capacity = tmp_capacity;
			}
			void					clear()
			{
				for (size_type i = this->_size; i > 0; i--)
					this->_alloc.destroy(&this->_memory[i - 1]);
				this->_size = 0;
			}

		friend bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			if (x._size != y._size)
				return (0);
			// remplacer par std::equal
			for (size_type i = 0; i < x._size; i++)
			{
				if (x._memory[i] != y._memory[i])
					return (0);
			}
			return (1);
		}
		friend bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
		}
	};
    
	// quand j'aurais finnis de faire les differentes classes iterators

	template <class T, class Allocator>
	bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
	{
		return ((x == y) ? 0 : 1);
	}
	template <class T, class Allocator>
	bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y)
	{
		return (y < x);
	}
	template <class T, class Allocator>
	bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
	{
		return ((y < x) || (x == y));
	}
	template <class T, class Allocator>
	bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
	{
		return ((x < y) || (x == y));
	}
	// specialized algorithms:
	template <class T, class Allocator>
	void swap(vector<T,Allocator>& x, vector<T,Allocator>& y)
	{
		x.swap(y);
	}
    
}

#endif
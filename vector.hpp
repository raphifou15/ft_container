#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iostream>
# include <stdexcept>
# include <sstream>

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
			//typedef implementation defined                	iterator; // See 23.1
			//typedef implementation defined					const_iterator; // See 23.1
			typedef typename Allocator::size_type				size_type; // See 23.1
			typedef typename Allocator::difference_type			difference_type;// See 23.1 The signed integer type describes an object that can represent the difference between the addresses of any two elements in a sequence that an object of template class allocator can allocate
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename Allocator::pointer					pointer;
			typedef typename Allocator::const_pointer			const_pointer;
			//typedef std::reverse_iterator<iterator>			reverse_iterator;
			//typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;
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
			
		/*
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const Allocator& = Allocator());
		*/
			vector(const vector<T,Allocator>& x) : _memory(x._memory), _size(x._size), _capacity(x._capacity)
			{
				this->_memory = this->_alloc.allocate(_capacity);
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(&this->_memory[i], x._memory[i]);
			}
			~vector()
			{
			  //std::cout << "memory destroy" << std::endl;
			  this->_alloc.deallocate(this->_memory, this->_capacity);
			}
        /*
			vector<T,Allocator>& operator=(const vector<T,Allocator>& x);
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last);
			void assign(size_type n, const T& u);
			allocator_type get_allocator() const;
		*/
		/*
			// iterators:
		
        
			iterator				begin();
			const_iterator			begin() const;
			iterator				end();
			const_iterator			end() const;
			reverse_iterator		rbegin();
			const_reverse_iterator 	rbegin() const;
			reverse_iterator 		rend();
			const_reverse_iterator 	rend() const;
		*/


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
					for (; sz > this->_size ; sz--)
					{
						this->_alloc.destroy(&this->_memory[sz]);
						this->_size--;
					}
				}
				if (sz > this->size())
				{
					if (sz > this->_capacity)
							this->reserve(sz);
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
					this->reallocateNumberOfCopy(n);
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
					throw std::length_error(lala);
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
					throw std::length_error(lala);
				}
				else
					return (this->_memory[n]);
			}
			reference				front()
			{
			 return (this->_memory[0]);
			 //appeler cette fonction sur un vector vide cause des comportements indefinis.
			}

			const_reference			front() const
			{
				return (this->_memory[0]);
			 	//appeler cette fonction sur un vector vide cause des comportements indefinis.
			}
			reference				back()
			{
				return (this->_memory[this->_size - 1]);
				//appeler cette fonction sur un vector vide cause des comportements indefinis.
			}
			const_reference			back() const
			{
				return (this->_memory[this->_size - 1]);
				//appeler cette fonction sur un vector vide cause des comportements indefinis.
			}
        
		// 23.2.4.3 modifiers:

        /*
			void					push_back(const T& x);
			void					pop_back();
			iterator				insert(iterator position, const T& x);
			void					insert(iterator position, size_type n, const T& x);
			template <class InputIterator>
			void					insert(iterator position, InputIterator first, InputIterator last);
			iterator				erase(iterator position);
			iterator				erase(iterator first, iterator last);
			void					swap(vector<T,Allocator>&);
			void					clear();
        */

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
	};
    

	/*
	// quand j'aurais finnis de faire les differentes classes iterators
	template <class T, class Allocator>
	bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	// specialized algorithms:
	template <class T, class Allocator>
	void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);
    */
}

#endif
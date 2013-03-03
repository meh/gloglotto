/** Copyleft (ɔ) meh. - http://meh.schizofreni.co
 *
 * This file is part of gloglotto - https://github.com/meh/gloglotto
 *
 * gloglotto is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * gloglotto is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gloglotto. If not, see <http://www.gnu.org/licenses/>.
 */

#include <gloglotto/vectors>

namespace gloglotto
{
	template <int Size, class Vector>
	vectors<Size, Vector>::vectors (void)
	{
		_data    = new type[Size * elements];
		_vectors = nullptr;

		std::fill(_data, _data + Size * elements, 0);

		own();
	}

	template <int Size, class Vector>
	vectors<Size, Vector>::vectors (type* pointer)
	{
		_data    = pointer;
		_vectors = nullptr;

		disown();
	}

	template <int Size, class Vector>
	vectors<Size, Vector>::vectors (vectors<Size, Vector> const& from)
	{
		_data    = new type[Size * elements];
		_vectors = nullptr;

		std::copy(&from, &from + Size * elements, _data);

		own();
	}

	template <int Size, class Vector>
	vectors<Size, Vector>::vectors (vectors<Size, Vector>&& from)
	{
		_data    = from._data;
		_vectors = from._vectors;

		from._vectors = nullptr;

		if (from.owner()) {
			from.disown();
			own();
		}
		else {
			disown();
		}
	}

	template <int Size, class Vector>
	vectors<Size, Vector>::vectors (std::initializer_list<std::initializer_list<type>> list) throw (std::invalid_argument)
	{
		_data    = new type[Size * elements];
		_vectors = nullptr;

		try {
			*this = list;
		}
		catch (std::invalid_argument& e) {
			delete[] _data;

			throw e;
		}

		own();
	}

	template <int Size, class Vector>
	vectors<Size, Vector>::~vectors (void)
	{
		if (owner()) {
			delete[] _data;
		}

		if (_vectors) {
			for (int i = 0; i < Size; i++) {
				if (_vectors[i]) {
					delete _vectors[i];
				}
			}
		}
	}

	template <int Size, class Vector>
	vectors<Size, Vector>&
	vectors<Size, Vector>::operator = (vectors<Size, Vector>&& from)
	{
		return swap(from);
	}

	template <int Size, class Vector>
	vectors<Size, Vector>&
	vectors<Size, Vector>::operator = (vectors<Size, Vector> const& from)
	{
		std::copy(&from, &from + Size * elements, _data);

		return *this;
	}

	template <int Size, class Vector>
	vectors<Size, Vector>&
	vectors<Size, Vector>::operator = (const type* from)
	{
		std::copy(from, from + Size * elements, _data);

		return *this;
	}

	template <int Size, class Vector>
	vectors<Size, Vector>&
	vectors<Size, Vector>::operator = (std::initializer_list<std::initializer_list<type>> list) throw (std::invalid_argument)
	{
		if (list.size() != Size) {
			throw std::invalid_argument("number of arguments doesn't match vectors size");
		}

		int i = 0;
		for (auto list : list) {
			if (list.size() != elements) {
				throw std::invalid_argument("number of arguments doesn't match vector size");
			}

			int j = 0;
			for (auto value : list) {
				_data[i * elements + j] = value;

				j++;
			}

			i++;
		}

		return *this;
	}

	template <int Size, typename Vector>
	bool
	vectors<Size, Vector>::owner (void) const
	{
		return _owner;
	}

	template <int Size, typename Vector>
	vectors<Size, Vector>&
	vectors<Size, Vector>::own (void)
	{
		_owner = true;

		return *this;
	}

	template <int Size, typename Vector>
	vectors<Size, Vector>&
	vectors<Size, Vector>::disown (void)
	{
		_owner = false;

		return *this;
	}

	template <int Size, typename Vector>
	vectors<Size, Vector>&
	vectors<Size, Vector>::swap (vectors<Size, Vector>& other)
	{
		auto data    = _data;
		auto owner   = _owner;
		auto vectors = _vectors;

		_data    = other._data;
		_owner   = other._owner;
		_vectors = other._vectors;

		other._data    = data;
		other._owner   = owner;
		other._vectors = vectors;

		return *this;
	}

	template <int Size, class Vector>
	Vector const&
	vectors<Size, Vector>::operator [] (int index) const throw (std::out_of_range)
	{
		if (index < 0 || index >= Size) {
			throw std::out_of_range("index out of range");
		}

		if (!_vectors) {
			_vectors = new Vector*[Size];
			std::fill(_vectors, _vectors + Size, nullptr);
		}

		if (!_vectors[index]) {
			_vectors[index] = new Vector(_data + (elements * index));
		}

		return *_vectors[index];
	}

	template <int Size, class Vector>
	typename vectors<Size, Vector>::const_iterator
	vectors<Size, Vector>::begin (void) const
	{
		return const_iterator(this);
	}

	template <int Size, class Vector>
	typename vectors<Size, Vector>::const_iterator
	vectors<Size, Vector>::end (void) const
	{
		return const_iterator(this, -1);
	}

	template <int Size, class Vector>
	Vector&
	vectors<Size, Vector>::operator [] (int index) throw (std::out_of_range)
	{
		if (index < 0 || index >= Size) {
			throw std::out_of_range("index out of range");
		}

		if (!_vectors) {
			_vectors = new Vector*[Size];
			std::fill(_vectors, _vectors + Size, nullptr);
		}

		if (!_vectors[index]) {
			_vectors[index] = new Vector(_data + (elements * index));
		}

		return *_vectors[index];
	}

	template <int Size, class Vector>
	typename vectors<Size, Vector>::iterator
	vectors<Size, Vector>::begin (void)
	{
		return iterator(this);
	}

	template <int Size, class Vector>
	typename vectors<Size, Vector>::iterator
	vectors<Size, Vector>::end (void)
	{
		return iterator(this, -1);
	}

	template <int Size, class Vector>
	typename vectors<Size, Vector>::type*
	vectors<Size, Vector>::operator & (void)
	{
		return _data;
	}

	template <int Size, class Vector>
	typename vectors<Size, Vector>::type const*
	vectors<Size, Vector>::operator & (void) const
	{
		return _data;
	}
}

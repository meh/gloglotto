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

#include <gloglotto/shader>
#include <gloglotto/utility>

namespace gloglotto
{
	template <typename Function>
	shader::shader (std::multimap<std::string, std::string> source, Function lambda) throw (invalid_operation, failed_compilation, failed_linking)
	{
		_id     = make(source);
		_source = source;

		auto function = new decltype(to_function(lambda))(to_function(lambda));

		_signature = &typeid(function);
		_function  = static_cast<void*>(function);
	}

	template <typename ...Args>
	void
	shader::begin (Args... args) throw (std::bad_typeid, invalid_operation, invalid_value)
	{
		if (_function) {
			auto function = static_cast<std::function<void(shader&, Args...)>*>(_function);

			if (typeid(function) == *_signature) {
				glUseProgram(_id);

				(*function)(*this, args...);
			}
			else {
				throw std::bad_typeid();
			}
		}
		else {
			if (typeid(void(Args...)) != typeid(void(void))) {
				throw std::bad_typeid();
			}

			glUseProgram(_id);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, std::array<float, Size> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform1fv(uniform(name), Size, data.data());
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, std::array<int, Size> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform1iv(uniform(name), Size, data.data());
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, std::array<unsigned int, Size> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform1uiv(uniform(name), Size, data.data());
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, std::array<bool, Size> data) throw (invalid_operation, invalid_value)
	{
		int buffer[Size];
		for (int i = 0; i < Size; i++) {
			buffer[i] = data[i];
		}

		check_exception {
			glUniform1iv(uniform(name), Size, &buffer);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<1, float>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform1fv(uniform(name), Size, &data);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<2, float>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform2fv(uniform(name), Size, &data);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<3, float>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform3fv(uniform(name), Size, &data);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<4, float>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform4fv(uniform(name), Size, &data);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<1, int>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform1iv(uniform(name), Size, &data);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<2, int>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform2iv(uniform(name), Size, &data);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<3, int>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform3iv(uniform(name), Size, &data);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<4, int>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform4iv(uniform(name), Size, &data);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<1, unsigned int>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform1uiv(uniform(name), Size, &data);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<2, unsigned int>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform2uiv(uniform(name), Size, &data);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<3, unsigned int>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform3uiv(uniform(name), Size, &data);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<4, unsigned int>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform4uiv(uniform(name), Size, &data);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<1, bool>> data) throw (invalid_operation, invalid_value)
	{
		int buffer[Size];
		for (int i = 0; i < Size; i++) {
			buffer[i] = (&data)[i];
		}

		check_exception {
			glUniform1iv(uniform(name), Size, buffer);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<2, bool>> data) throw (invalid_operation, invalid_value)
	{
		int buffer[Size * 2];
		for (int i = 0; i < Size * 2; i++) {
			buffer[i] = (&data)[i];
		}

		check_exception {
			glUniform2iv(uniform(name), Size, buffer);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<3, bool>> data) throw (invalid_operation, invalid_value)
	{
		int buffer[Size * 3];
		for (int i = 0; i < Size * 3; i++) {
			buffer[i] = (&data)[i];
		}

		check_exception {
			glUniform3iv(uniform(name), Size, buffer);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<4, bool>> data) throw (invalid_operation, invalid_value)
	{
		int buffer[Size * 4];
		for (int i = 0; i < Size * 4; i++) {
			buffer[i] = (&data)[i];
		}

		check_exception {
			glUniform4iv(uniform(name), Size, buffer);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, matrices<Size, matrix<2, 2, float>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniformMatrix2fv(uniform(name), Size, GL_TRUE, &data);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, matrices<Size, matrix<3, 3, float>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniformMatrix3fv(uniform(name), Size, GL_TRUE, &data);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, matrices<Size, matrix<4, 4, float>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniformMatrix4fv(uniform(name), Size, GL_TRUE, &data);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, matrices<Size, matrix<2, 3, float>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniformMatrix3x2fv(uniform(name), Size, GL_TRUE, &data);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, matrices<Size, matrix<3, 2, float>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniformMatrix2x3fv(uniform(name), Size, GL_TRUE, &data);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, matrices<Size, matrix<2, 4, float>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniformMatrix4x2fv(uniform(name), Size, GL_TRUE, &data);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, matrices<Size, matrix<4, 2, float>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniformMatrix2x4fv(uniform(name), Size, GL_TRUE, &data);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, matrices<Size, matrix<3, 4, float>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniformMatrix4x3fv(uniform(name), Size, GL_TRUE, &data);
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, matrices<Size, matrix<4, 3, float>> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniformMatrix3x4fv(uniform(name), Size, GL_TRUE, &data);
		}
	}
}

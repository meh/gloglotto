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

#include <gloglotto/shader_manager>

namespace gloglotto
{
	shader_manager::shader_manager (void)
	{
	}

	shader_manager::~shader_manager (void)
	{
		for (auto entry : _shaders) {
			delete entry.second;
		}
	}

	shader*
	shader_manager::make (std::multimap<std::string, std::string> source)
	{
		return new shader(source);
	}

	shader&
	shader_manager::add (std::string name, std::multimap<std::string, std::string> source)
	{
		auto current = make(source);

		_shaders[name] = current;

		return *current;
	}

	shader&
	shader_manager::get (std::string name)
	{
		return *_shaders.at(name);
	}

	shader_manager::shader_in_use::shader_in_use (shader* in_use)
	{
		_shader = in_use;
	}

	shader*
	shader_manager::shader_in_use::begin (void)
	{
		return _shader;
	}

	shader*
	shader_manager::shader_in_use::end (void)
	{
		return _shader + 1;
	}

	shader&
	shader_manager::shader_in_use::operator * (void)
	{
		return *_shader;
	}
}

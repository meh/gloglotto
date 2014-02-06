#include <iostream>
#include <gl>

int
main (int argc, char* argv[])
{
	gl::window::create(&argc, argv, { 400, 400 }, "Triangle");

	gl::shader_manager shaders;
	shaders.add("arcobaleno", {
		{ "vertex", R"(#version 120
			attribute vec3 vertex;
			attribute vec3 vertex_color;

			varying vec4 color;

			void
			main (void)
			{
				gl_Position = vec4(vertex.x, vertex.y, vertex.z, 1.0);
				color       = vec4(vertex_color.r, vertex_color.g, vertex_color.b, 1.0);
			}
		)" },

		{ "fragment", R"(#version 120
			varying vec4 color;

			void
			main (void)
			{
				gl_FragColor = color;
			}
		)" } });

	gl::window::on<gl::window::event::keyboard>([](gl::window::key& key, int x, int y) {
		(void) x;
		(void) y;

		if (key == gl::window::key::esc || key == 'q') {
			gl::window::exit();
		}
	});

	gl::window::on<gl::window::event::resize>([](int w, int h) {
		gl::viewport(w, h);
	});

	gl::window::on<gl::window::event::render>([&] {
		static gl::vectors<6, gl::vector<3>> triangle {
			{  0.00,  1.00, 0.0 },
			{  0.87, -0.50, 0.0 },
			{ -0.87, -0.50, 0.0 },
				
			{ 1.0, 0.0, 0.0 },
			{ 0.0, 1.0, 0.0 },
			{ 0.0, 0.0, 1.0 } };

		static gl::buffer buffer(gl::target::vertex::data, gl::usage::stream::draw, triangle);

		static auto beginning = std::chrono::high_resolution_clock::now();
		       auto now       = std::chrono::high_resolution_clock::now();

		int tick = std::chrono::duration_cast<std::chrono::milliseconds>(now - beginning).count();
		{
			auto rotated = triangle;

			rotated.slice<3>() *= gl::make::rotation(gl::angle::radians::make(tick / 1000.0), 0.0f, 0.0f, 1.0f);

			buffer.replace(gl::target::vertex::data, rotated);
		}

		gl::clear(gl::clear::color | gl::clear::depth | gl::clear::stencil);

		with_shader(shaders, "arcobaleno") {
			self.use(buffer);
			self.attribute<gl::vector<3>>("vertex");
			self.attribute<gl::vector<3>>("vertex_color", gl::vector<3>::bytes * 3);

			self.draw(gl::primitive::triangle, 3);
		}

		gl::window::render();
		gl::window::update();
	});

	gl::window::loop([] {
		gl::clear(gl::clear::color, 0, 0, 0);
	});
}

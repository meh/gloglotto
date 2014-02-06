#include <amirite>
#include <gl>

int
main (int argc, char* argv[])
{
	(void) argc;
	(void) argv;

	return amirite("rgba", {
		{ "size", []{
			gl::image::format::rgba<2> colors(2);

			amiequal(colors.size(), 2u);
			amiequal(colors.byte_size(), 2u);
		}},

		{ "access", []{
			gl::image::format::rgba<2> colors(2);

			colors[0]->r = 1;
			colors[0]->g = 2;
			colors[0]->b = 2;

			amiequal(colors[0]->r, 1u);
			amiequal(colors[0]->g, 2u);
			amiequal(colors[0]->b, 2u);
			amiequal(colors[0]->a, 0u);
		}},

		{ "foreach", []{
			gl::image::format::rgba<2> colors(2);

			colors[0]->r = 1;
			colors[0]->g = 2;
			colors[0]->b = 2;

			int i = 0;
			for (auto color : colors) {
				switch (i) {
					case 0:
						amiequal(color->r, 1u);
						amiequal(color->g, 2u);
						amiequal(color->b, 2u);
						amiequal(color->a, 0u);
						break;

					case 1:
						amiequal(color->r, 0u);
						amiequal(color->g, 0u);
						amiequal(color->b, 0u);
						amiequal(color->a, 0u);
						break;
				}

				i++;
			}
		}}
	});
}

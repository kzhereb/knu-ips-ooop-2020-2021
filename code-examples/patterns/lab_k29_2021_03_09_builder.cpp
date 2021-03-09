/*
 * lab_k29_2021_03_09_builder.cpp
 *
 *  Created on: Mar 9, 2021
 *      Author: KZ
 */

#include "../doctest.h"

#include <string>
#include <sstream>

class HtmlBuilder {
private:
	std::stringstream current_html;
public:
	static std::string html_encode(std::string text) {
		return text; //TODO: implement me!
	}
	void add_text(std::string text) {
		current_html << "<p>"<< html_encode(text)<<"</p>"<<std::endl;
	}
	void add_title(std::string text, int level) {
		std::string header_tag = "h"+std::to_string(level);
		current_html << "<"<<header_tag<<">"<<html_encode(text)<<"</"<<header_tag<<">"<<std::endl;
	}
	void add_link(std::string url, std::string text) {
		current_html << "<a href='"<<url<<"'>"<<html_encode(text)<<"</a>"<<std::endl;
	}
	void add_image(std::string img_url, std::string alt_text) {
		current_html << "<img src='"<<img_url<<"' alt='"<<html_encode(alt_text)<<"'>"<<std::endl;
	}

	std::string get_html() {
		return current_html.str();
	}
};

TEST_CASE("building HTML using Builder pattern") {
	HtmlBuilder builder;
	builder.add_title("New Cars", 1);
	builder.add_title("Buy now!", 2);
	builder.add_text("Buy our new cars at considerable discount");
	builder.add_link("https://carsales.com/buy", "Buy a new car");
	CHECK(builder.get_html() == std::string(
			"<h1>New Cars</h1>\n"
			"<h2>Buy now!</h2>\n"
			"<p>Buy our new cars at considerable discount</p>\n"
			"<a href='https://carsales.com/buy'>Buy a new car</a>\n"
			));
}



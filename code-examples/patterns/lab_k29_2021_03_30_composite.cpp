/*
 * lab_k29_2021_03_30_composite.cpp
 *
 *  Created on: Mar 30, 2021
 *      Author: KZ
 */


#include "../doctest.h"

#include <string>
#include <memory>
#include <vector>
#include <stdexcept>


class FileSystemItem {
protected:
	std::string _name;
public:
	FileSystemItem(std::string name): _name{name} {}
	std::string name() { return _name; }
	virtual int size() = 0;

	virtual void add_child(std::shared_ptr<FileSystemItem> child) {
		throw std::logic_error("Can't add children to this object");
	}

	virtual std::size_t children_count() {
		return 0;
	}
};

class File: public FileSystemItem {
private:
	int _size;
public:
	File(std::string name, int size): FileSystemItem(name), _size{size} {}
	int size() override {
		return _size;
	}
};

class Directory: public FileSystemItem {
private:
	std::vector<std::shared_ptr<FileSystemItem>> children;
public:
	Directory(std::string name): FileSystemItem(name) {}

	int size() override {
		int result = 0;
		for(std::shared_ptr<FileSystemItem> child: children) {
			result += child->size();
		}
		return result;
	}

	void add_child(std::shared_ptr<FileSystemItem> child) override {
		children.push_back(child);
	}

	std::size_t children_count() override {
		return children.size();
	}
};

TEST_CASE("working with filesystem (composite)") {
	auto root_dir = std::make_shared<Directory>("root");
	root_dir->add_child(std::make_shared<File>("config.json", 1000));
	root_dir->add_child(std::make_shared<File>("data.bin", 55000));

	auto child_dir = std::make_shared<Directory>("child");
	child_dir->add_child(std::make_shared<File>("readme.txt", 123));
	root_dir->add_child(child_dir);

	CHECK(child_dir->size() == 123);
	CHECK(root_dir->size() == 56123);
}


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
#include <ostream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>


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


class LoggingFileSystemItem: public FileSystemItem {
private:
	std::shared_ptr<FileSystemItem> decorated_item;
	std::ostream& log_stream;

public:
	LoggingFileSystemItem(std::shared_ptr<FileSystemItem> decorated_item, std::ostream& log_stream) :
		FileSystemItem{decorated_item->name()}, decorated_item{decorated_item}, log_stream{log_stream} {}

		int size() override {
			log_stream<<"Getting size for "<<decorated_item->name()<<std::endl;
			int result = decorated_item->size();
			log_stream<<"Size for "<<decorated_item->name()<<" is " <<result<<std::endl;
			return result;

		}

		void add_child(std::shared_ptr<FileSystemItem> child) override {
			log_stream<<"Trying to add child "<<child->name()<<" to item "<<decorated_item->name()
					<<" with children_count = "<<decorated_item->children_count()<<std::endl;
			decorated_item->add_child(child);
			log_stream<<"Child added successfully, new children_count = "<<decorated_item->children_count()<<std::endl;
		}

		std::size_t children_count() override {
			log_stream<<"Getting children_count for "<<decorated_item->name()<<std::endl;
			std::size_t result = decorated_item->children_count();
			log_stream<<"children_count for "<<decorated_item->name()<<" is " <<result<<std::endl;
			return result;
		}

};

TEST_CASE("using decorator to log API calls") {
  std::stringstream log;
  auto root_dir_real = std::make_shared<Directory>("root");
  auto root_dir = std::make_shared<LoggingFileSystemItem>(root_dir_real, log);

  root_dir->add_child(std::make_shared<File>("config.json", 1000));
  root_dir->add_child(std::make_shared<File>("data.bin", 55000));

  auto child_dir = std::make_shared<Directory>("child");
  child_dir->add_child(std::make_shared<File>("readme.txt", 123));
  root_dir->add_child(child_dir);



  CHECK(child_dir->size() == 123);
  CHECK(root_dir->size() == 56123);

  CHECK(log.str()==std::string(
          "Trying to add child config.json to item root with children_count = 0\n"
          "Child added successfully, new children_count = 1\n"
          "Trying to add child data.bin to item root with children_count = 1\n"
          "Child added successfully, new children_count = 2\n"
          "Trying to add child child to item root with children_count = 2\n"
          "Child added successfully, new children_count = 3\n"
          "Getting size for root\n"
          "Size for root is 56123\n"));
}


class TimeMeasureFileSystemItem: public FileSystemItem {
private:
  std::shared_ptr<FileSystemItem> decorated_item;
public:
  TimeMeasureFileSystemItem(std::shared_ptr<FileSystemItem> decorated_item) :
    FileSystemItem{decorated_item->name()}, decorated_item{decorated_item} {}

  int size() override {
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();

    int result = decorated_item->size();

    std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
    std::cout << "Time for item " << decorated_item->name() << ", operation size(): "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
            << "ms" << std::endl;
    return result;
  }

  void add_child(std::shared_ptr<FileSystemItem> child) override {
    decorated_item->add_child(child);
  }
};


class DelayFileSystemItem: public FileSystemItem {
private:
  std::shared_ptr<FileSystemItem> decorated_item;
  int delay_ms;
public:
  DelayFileSystemItem(std::shared_ptr<FileSystemItem> decorated_item, int delay_ms) :
    FileSystemItem{decorated_item->name()}, decorated_item{decorated_item}, delay_ms{delay_ms} {}

  int size() override {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));

    int result = decorated_item->size();

    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    return result;
  }

  void add_child(std::shared_ptr<FileSystemItem> child) override {
    decorated_item->add_child(child);
  }
};

TEST_CASE("using decorator to measure API calls time") {
  std::stringstream log;
  auto root_dir_real = std::make_shared<Directory>("root");
  auto root_dir_delay = std::make_shared<DelayFileSystemItem>(root_dir_real, 20);
  auto root_dir_delay2 = std::make_shared<DelayFileSystemItem>(root_dir_delay, 100);
  auto root_dir = std::make_shared<TimeMeasureFileSystemItem>(root_dir_delay2);

  root_dir->add_child(std::make_shared<File>("config.json", 1000));
  root_dir->add_child(std::make_shared<File>("data.bin", 55000));

  auto child_dir = std::make_shared<Directory>("child");
  child_dir->add_child(std::make_shared<File>("readme.txt", 123));
  root_dir->add_child(child_dir);



  CHECK(child_dir->size() == 123);
  CHECK(root_dir->size() == 56123);
}

//std::shared_ptr<>

std::shared_ptr<FileSystemItem> create_decorated_file(std::string filename, int size) {
  return std::make_shared<TimeMeasureFileSystemItem>(
      std::make_shared<DelayFileSystemItem>(
          std::make_shared<DelayFileSystemItem>(
              std::make_shared<File>(filename, size), 20), 100));
}

std::shared_ptr<FileSystemItem> create_decorated_directory(std::string filename) {
  return std::make_shared<TimeMeasureFileSystemItem>(
      std::make_shared<DelayFileSystemItem>(
          std::make_shared<DelayFileSystemItem>(
              std::make_shared<Directory>(filename), 20), 100));
}

TEST_CASE("using decorator to measure API calls time, all items decorated") {
  std::stringstream log;
  auto root_dir = create_decorated_directory("root");

  root_dir->add_child(create_decorated_file("config.json", 1000));
  root_dir->add_child(create_decorated_file("data.bin", 55000));

  auto child_dir = create_decorated_directory("child");
  child_dir->add_child(create_decorated_file("readme.txt", 123));
  root_dir->add_child(child_dir);



  CHECK(child_dir->size() == 123);
  CHECK(root_dir->size() == 56123);
}



class FileSystemItemFactory {
public:
	virtual std::shared_ptr<FileSystemItem> create_file(std::string name, int size) {
		return std::make_shared<File>(name, size);
	}

	virtual std::shared_ptr<FileSystemItem> create_directory(std::string name) {
		return std::make_shared<Directory>(name);
	}

};

class LoggingFileSystemItemFactory: public FileSystemItemFactory {
private:
	std::ostream& log_stream;
public:
	LoggingFileSystemItemFactory(std::ostream& log_stream): log_stream{log_stream} {}

	std::shared_ptr<FileSystemItem> create_file(std::string name, int size) override {
		std::shared_ptr<FileSystemItem> file_real = FileSystemItemFactory::create_file(name, size);
		return std::make_shared<LoggingFileSystemItem>(file_real, log_stream);
	}

	std::shared_ptr<FileSystemItem> create_directory(std::string name) override {
		std::shared_ptr<FileSystemItem> dir_real = FileSystemItemFactory::create_directory(name);
		return std::make_shared<LoggingFileSystemItem>(dir_real, log_stream);
	}
};





TEST_CASE("using decorator to log API calls") {
	std::stringstream log;
	LoggingFileSystemItemFactory factory{log};

	auto root_dir = factory.create_directory("root");

	root_dir->add_child(factory.create_file("config.json", 1000));
	root_dir->add_child(factory.create_file("data.bin", 55000));

	auto child_dir = factory.create_directory("child");
	child_dir->add_child(factory.create_file("readme.txt", 123));
	root_dir->add_child(child_dir);



	CHECK(child_dir->size() == 123);
	CHECK(root_dir->size() == 56123);

	CHECK(log.str()==std::string(
			"Trying to add child config.json to item root with children_count = 0\n"
			"Child added successfully, new children_count = 1\n"
			"Trying to add child data.bin to item root with children_count = 1\n"
			"Child added successfully, new children_count = 2\n"
			"Trying to add child readme.txt to item child with children_count = 0\n"
			"Child added successfully, new children_count = 1\n"
			"Trying to add child child to item root with children_count = 2\n"
			"Child added successfully, new children_count = 3\n"
			"Getting size for child\n"
			"Getting size for readme.txt\n"
			"Size for readme.txt is 123\n"
			"Size for child is 123\n"
			"Getting size for root\n"
			"Getting size for config.json\n"
			"Size for config.json is 1000\n"
			"Getting size for data.bin\n"
			"Size for data.bin is 55000\n"
			"Getting size for child\n"
			"Getting size for readme.txt\n"
			"Size for readme.txt is 123\n"
			"Size for child is 123\n"
			"Size for root is 56123\n"));
}

//TEST_CASE("test old code") {
//std::cout<<"hello legacy code"<<std::endl;
//}


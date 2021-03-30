/*
 * lab_k29_2021_03_30_composite.cpp
 *
 *  Created on: Mar 30, 2021
 *      Author: KZ
 */


#include "../doctest.h"

#include <string>
#include <memory>
#include <stdexcept>


class FileSystemItem {
public:
	std::string name();
	virtual int size() = 0;

	virtual void add_child(std::shared_ptr<FileSystemItem> child) {
		throw std::logic_error("Can't add children to this object");
	}
};


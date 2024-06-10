#pragma once
#include <iostream>
#include <string>

class mail_Exception :public std::exception {
public:
	mail_Exception(const std::string& msg) { message_ = msg; }
	mail_Exception():message_() {};
	virtual const char* what() const override {
		return message_.c_str();
	}
protected:
	std::string message_;
};


class save_Missing : public mail_Exception {
public:
	save_Missing(const std::string& msg):mail_Exception(msg) {}
};

class wrong_JSON_Format : public mail_Exception {
public:
	wrong_JSON_Format(const std::string& path) :mail_Exception() {
		path_ = path;
		message_ = "Objeto en "+path+ "no es del tipo esperado";
	}
protected:
	std::string path_;
};


class config_File_Missing :public mail_Exception {
public:
	config_File_Missing(const std::string& path):mail_Exception() {
		path_ = path;
		message_ = "Archvo con ruta " + path  + "no pudo encontrarse";
	}
protected:
	std::string path_;
};

class texture_load_fail :public mail_Exception {
public:
	texture_load_fail() :mail_Exception() {
		message_ = "Error al cargar la textura, se generara placeholder";
	}
};

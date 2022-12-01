#pragma once
#include <string>

enum class CmdId : int {
	Advance,
	RotateLeft,
	RotateRight,
	Reset,
	PenDown,
	PenUp,
	Speed,
	Color,
};

struct Cmd {
	CmdId	id = CmdId::Reset;
	float	data = 0;
	float	data2 = 0;
	float	data3 = 0;
};

class CmdFile{
public:

	static std::vector<Cmd> load(std::string path) {
		std::vector<Cmd> res;
		FILE* f = nullptr;
		fopen_s(&f, path.c_str(), "r");
		if (!f)
			return res;

		int nbRead = 0;
		do{
			Cmd c;
			nbRead = fscanf_s(f, "%d %f\n", &c.id, &c.data);
			if(nbRead>0)
				res.push_back(c);
		} 
		while (nbRead>0);
		fclose(f);
		return res;
	};

	static bool save(std::string path, std::vector<Cmd> & data ) {
		FILE* f = nullptr;
		fopen_s(&f,path.c_str(), "w");
		if (!f)
			return false;
		for( auto & cmd : data )
			fprintf(f, "%d %llf\n", cmd.id, cmd.data);
		fflush(f);
		fclose(f);
		return true;
	}

	static std::vector<Cmd> loadScript(std::string path) {
		std::vector<Cmd> res;
		FILE* f = nullptr;
		fopen_s(&f, path.c_str(), "r");
		if (!f)
			return res;

		int nbRead = 0;
		char cmdName[128] = {};
		do {
			Cmd c;
			c.id = CmdId::Advance;
			c.data = 0.0f;
			cmdName[0] = 0;
			
			auto pos = ftell(f);
			if( (nbRead=fscanf_s(f,"Color (%f,%f,%f)\n", &c.data, &c.data2, &c.data3)) > 0 ){
				c.id = CmdId::Color;
				res.push_back(c);
			}
			else {
				fseek(f, pos, 0);
				nbRead = fscanf_s(f, "%s %f\n", cmdName, 128,&c.data);
				if (0 == strcmp(cmdName, "Advance"))		c.id = CmdId::Advance;
				if (0 == strcmp(cmdName, "RotateLeft"))		c.id = CmdId::RotateLeft;
				if (0 == strcmp(cmdName, "RotateRight"))	c.id = CmdId::RotateRight;
				if (0 == strcmp(cmdName, "Reset"))			c.id = CmdId::Reset;
				if (0 == strcmp(cmdName, "PenUp"))			c.id = CmdId::PenUp;
				if (0 == strcmp(cmdName, "PenDown"))		c.id = CmdId::PenDown;
				if (0 == strcmp(cmdName, "Speed"))			c.id = CmdId::Speed;
				if (nbRead > 0)
					res.push_back(c);
			}
		} while (nbRead > 0);
		fclose(f);
		return res;
	};

	static bool saveScript(std::string path, std::vector<Cmd>& data) {
		FILE* f = nullptr;
		fopen_s(&f, path.c_str(), "w");
		if (!f)
			return false;
		for (auto& cmd : data) {
			switch (cmd.id) {
			case CmdId::Advance:		fprintf(f, "Advance %f\n",  cmd.data); break;
			case CmdId::RotateLeft:		fprintf(f, "RotateLeft %f\n", cmd.data); break;
			case CmdId::RotateRight:	fprintf(f, "RotateRight %f\n", cmd.data); break;
			case CmdId::Reset:			fprintf(f, "Reset \n"); break;
			case CmdId::PenDown:		fprintf(f, "PenDown \n"); break;
			case CmdId::PenUp:			fprintf(f, "PenUp \n"); break;
			case CmdId::Speed:			fprintf(f, "Speed %f \n"); break;
			case CmdId::Color:			fprintf(f, "Color (%f,%f,%f) \n", cmd.data,cmd.data2,cmd.data3); break;
			default:
				break;
			}
		}
		fflush(f);
		fclose(f);
		return true;
	}
};
#pragma once
class ValidadorDelColor
{
private:
	std::vector<int> colorAlternativo;

public:
	ValidadorDelColor();
	void validarColorDesde(Json::Value color_alternativo);
	std::vector<int> getColorAlternativo();
	~ValidadorDelColor();
};


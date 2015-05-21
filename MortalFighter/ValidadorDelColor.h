#pragma once
class ValidadorDelColor
{
private:
	std::vector<double> colorAlternativo;

public:
	ValidadorDelColor();
	void validarColorDesde(Json::Value color_alternativo);
	std::vector<double> getColorAlternativo();
	~ValidadorDelColor();
};


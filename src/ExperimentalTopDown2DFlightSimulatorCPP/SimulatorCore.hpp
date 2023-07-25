#include <thread>

#include <vector>

#include <Vector2.hpp>

#include <TileMap.hpp>

#include <HTTPClient.hpp>

#include <File.hpp>

class SimulatorCore
{
private:
	const godot::String OVERPASS_API_ENDPOINT_URL = "https://maps.mail.ru/osm/tools/overpass/api/interpreter";

	godot::HTTPClient* httpClientPtr;

	godot::PoolStringArray defaultHTTPRequestHeaders;

	godot::String GenerateOverpassAPISingaporeLocationDataURL();

	bool HandleError(godot::Error error);

	void FetchOSMDataForWorldMap();
public:
	static SimulatorCore* instancePtr;

	SimulatorCore();

	static void _register_methods();

	void _init();

	void _ready();

	static godot::String GetBooleanAsString(bool boolean);

	void GenerateRandomWorld(godot::TileMap* tileMapPtr);

	void GenerateWorld(godot::Node2D* mainWorldRootPtr);
};
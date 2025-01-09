#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

namespace Engine
{
	class AssetManager
	{
	public:
		AssetManager();
		~AssetManager();

		void addTexture(int id, const string& filepath, bool repeated = false) {}
		void addFont(int id, const string& filepath);

		const sf::Texture& getTexture(int id) const;
		const sf::Font& getFont(int id) const;

	private:
		map<int, unique_ptr<sf::Texture>> _texture;
		map<int, unique_ptr<sf::Font>> _font;
	};
}

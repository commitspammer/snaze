#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <string>

using namespace std;

class Parser {
	private:
		/**@brief List of layouts as vectors of strings.
		 * A layout's first line holds the level values.
		 * A layout's second line and forward hold the map's drawing.
		 */
		vector<vector<string>> layouts;

	public:
		/**@brief Attempts to open a file.
		 * @param path File path.
		 * @return True if file was opened successfully; false if not.
		 */
		bool try_open_file(string path);

		/**@brief Checks if a gamemode is valid.
		 * @param mode Gamemode.
		 * @return True if mode is valid; false if not.
		 */
		bool parse_mode(string mode);

		/**@brief NOT IMPLEMENTED! */
		bool parse_level_file(string path);

		/**@brief Reads layouts from a level file. Stores them in list of layouts.
		 * @param path File path.
		 */
		void separate_layouts_from_level_file(string path);

		/**@brief Outputs, and then removes, a layout from list of layouts.
		 * @param buffer Vector to receive layout.
		 * @return True if a layout was found in the list; false if not.
		 */
		bool get_next_layout(vector<string>* buffer);
};

#endif


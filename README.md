# Main Level Editor (Geode mod)

Change the **name**, **ID** and **difficulty face** of any main level (1–22) from the mod's settings. Main levels only.

## How to use it
Open Geode > Main Level Editor > Settings. For each level you get:
- **Name** – type whatever you want (leave blank to keep the original)
- **ID** – type a new ID (0 = unchanged)
- **Difficulty Face** – pick any face, or "Default"

Restart the game after changing settings so every menu picks them up.

## Getting your .geode file (no coding needed)
1. Make a free account at github.com and create a new empty repository.
2. Upload everything in this folder (src/, .github/, mod.json, CMakeLists.txt) to it.
3. Open the **Actions** tab. The "Build Geode Mod" workflow runs automatically (or press "Run workflow").
4. When it finishes, open the run and download **Build Output**. Inside is your `.geode` file.
5. Put the `.geode` in your Geometry Dash `geode/mods` folder.

## Before building
- In `mod.json`, change `"yourname"` in `id` and `developer` to your own name (lowercase, no spaces).
- Changing a level's ID can affect completion/stat tracking, since the game tracks main levels by ID. Name and face changes are safe.

## Note
This was written without being compiled. If the GitHub build reports an error, paste it back and it can be fixed (Geode bindings change between versions).

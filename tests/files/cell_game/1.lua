local EMPTY = 0
local OCCUPIED = 1

cur = { x = 0, y = 0 }

map = {}

function set_map(x, y, status)
	if not map[x] then
		map[x] = {}
	end
	map[x][y] = status
end

function search_nearest()
	local s = search() -- Search for nearest 9 cells
	for x, row in pairs(s) do
		for y, status in pairs(row) do
			set_map(cur.x + x, cur.y + y, status)
		end
	end
end

while true do
end

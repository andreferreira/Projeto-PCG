local x = 1024
local y = 60000

math.randomseed( os.time() )

function enemies()
	local e = { }
	for i = 1, 20 do
		e[i] = {name = "Soldier", spawn = {math.random(1000), i*3000}}
	end
	return e
end

map {
	spawn = {x/2, y-250},
	width = x,
	height = y,
	platforms = {
		platform{0, y-250, x, y-250, passable = false},
	},
	weapons = {
		{name = "Flamethrower", spawn = {x/3, y-5000}},
	},
	enemies = enemies()
}

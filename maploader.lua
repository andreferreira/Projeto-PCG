function map(t)
	regmap(t.width,t.height,t.spawn[1],t.spawn[2])
	for i,p in pairs(t.platforms) do
		regplatform(p[1],p[2],p[3],p[4],p.passable,p.color[1],p.color[2],p.color[3])
	end
	for i,w in pairs(t.weapons) do
		regweapon(w.name, w.spawn[1], w.spawn[2])
	end
	for i,e in pairs(t.enemies) do
		regenemy(e.name, e.spawn[1], e.spawn[2])
	end
	return t
end

function platform(t)
	if t.passable == nil then
		t.passable = true
	end
	if t.color == nil then
		if t.passable then
			t.color = {0.5,0.5,0.5}
		else
			t.color = {0,0,0}
		end
	end
	return t
end

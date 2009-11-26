function map(t)
	regmap(t.width,t.height,t.spawn[1],t.spawn[2])
	for i,p in pairs(t.platforms) do
		regplatform(p[1],p[2],p[3],p[4],p.passable)
	end
	for i,w in pairs(t.weapons) do
		regweapon(w.name, w.spawn[1], w.spawn[2])
	end
	return t
end

function platform(t)
	if t.passable == nil then
		t.passable = true
	end
	return t
end

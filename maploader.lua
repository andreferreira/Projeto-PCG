function map(t)
	regmap(t.width,t.height)
	for i,p in pairs(t.platforms) do
		regplatform(p[1],p[2],p[3],p[4],p.passable)
	end
	return t
end

function platform(t)
	if t.passable == nil then
		t.passable = true
	end
	return t
end

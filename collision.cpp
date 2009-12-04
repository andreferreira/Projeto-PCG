#include "collision.h"

void CollisionManager::subscribe(Thing* thing){
	things.insert(thing);
}

void CollisionManager::remove(Thing* thing){
	things.erase(thing);
}

void CollisionManager::update(){
	std::set<Thing*>::iterator it1,it2;
	for (it1 = things.begin(); it1 != things.end(); it1++) {
		for (it2 = it1; it2 != things.end(); it2++) {
			if (*it1 == *it2) continue;
			checkCollision(*it1,*it2);
		}
	}
}

bool pointInsidePolygon(Ponto ponto, Polygon p) {
	std::vector<Linha>::iterator it;
	Ponto infinito(0xffffff,ponto.y);
	int inter = 0;
	Linha toinfinity(ponto,infinito);
	for (it = p.linhas.begin(); it != p.linhas.end(); it++) {
		if (linesIntersect(*it,toinfinity)) {
			inter++;
		}
	}
	if (inter % 2 == 1)
		return true;
	else
		return false;
}

bool CollisionManager::checkCollision(Thing* a, Thing* b){
	Polygon pa,pb;
	pa = a->getCollision();
	pb = b->getCollision();
	pa.translate(a->getPosition());
	pb.translate(b->getPosition());
	std::vector<Linha>::iterator ita,itb;
	if (pointInsidePolygon(pb.linhas[0].vertices[0],pa)) {
		a->collide(b);
		b->collide(a);
		return true;
	}
	for (ita = pa.linhas.begin(); ita != pa.linhas.end(); ita++) {
		for (itb = pb.linhas.begin(); itb != pb.linhas.end(); itb++) {
			/*std::cout<<"A:"<<(*ita).vertices[0].x<<" "<<(*ita).vertices[0].y<<" "
					 <<(*ita).vertices[1].x<<" "<<(*ita).vertices[1].y<<std::endl;
			std::cout<<"B:"<<(*itb).vertices[0].x<<" "<<(*itb).vertices[0].y<<" "
					 <<(*itb).vertices[1].x<<" "<<(*itb).vertices[1].y<<std::endl;*/
			if (linesIntersect(*ita,*itb)) {
				a->collide(b);
				b->collide(a);
				return true;
			}
		}
	}
	return false;
}

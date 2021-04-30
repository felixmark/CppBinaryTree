template<typename T> class Sakura {
	private:
        size_t MAX_SIZE = 5; //     max. Anzahl an gespeicherten Objekten pro Blatt
		size_t inhaltZahl;
		size_t depth;
		bool isLeaf;
		Sakura *unterknoten;
		Sakura *unterknoten2;
		T richtung;
		T *inhalt;
		void sort() {
			for(size_t o = 0; o < MAX_SIZE; ++o)
				for(size_t i = 0; i < inhaltZahl-1; ++i)
					if (inhalt[i+1] < inhalt[i])
						std::swap(inhalt[i],inhalt[i+1]);
		}
        protected : T* getInhalt(){
            return inhalt;
        }
	public:
		Sakura() {
			inhaltZahl = 0;
			inhalt = new T[MAX_SIZE];
			isLeaf = true;
			unterknoten = NULL;
			unterknoten2 = NULL;
		}
		~Sakura() {
			delete unterknoten;
			delete unterknoten2;
			delete [] inhalt;
		}
		bool istBlatt() {
			return isLeaf;
		}
		void add(T daten) {
			if (inhaltZahl == MAX_SIZE) {
				if (isLeaf) {
					unterknoten = new Sakura;
					unterknoten2 = new Sakura;
					unterknoten->setTiefe(depth+1);
					unterknoten2->setTiefe(depth+1);

					sort();
                    richtung = inhalt[MAX_SIZE/2-1]; //-1 wegen 0-X

					for (size_t i = 0; i < MAX_SIZE/2; ++i)
						if (!(richtung < inhalt[i])) unterknoten->add(inhalt[i]);
						else unterknoten2->add(inhalt[i]);

					for (size_t i = MAX_SIZE/2; i < MAX_SIZE; ++i)
						if (!(richtung < inhalt[i])) unterknoten->add(inhalt[i]);
						else unterknoten2->add(inhalt[i]);

					delete [] inhalt;
					inhalt = NULL;
					inhaltZahl = MAX_SIZE;
					isLeaf = false;
				}
				if (!(richtung < daten)) unterknoten->add(daten);
				else unterknoten2->add(daten);
			}
			else {
				inhalt[inhaltZahl++] = daten;
				sort();
			}
		}

        size_t count(size_t count) {
			if (isLeaf) {
				return count+inhaltZahl;
			} else {
				size_t c1 = unterknoten->count(count);
				size_t c2 = unterknoten2->count(count);
				return c1 + c2;
			}
		}

		void print(size_t layer, bool flat) {
		    if (depth != layer && layer != -1UL) {
                if (!isLeaf && depth <= layer) {
                    unterknoten->print(layer, flat);
                    unterknoten2->print(layer, flat);
                }
                return;
		    }

			if (isLeaf) {
                if (depth <= layer || layer == -1UL) {
                    if (flat) {
                         for (size_t i = 0; i < inhaltZahl; ++i) {
                            std::cout << inhalt[i] << " ";
                        }
                    } else {
                        for (size_t i = 0; i < depth; ++i) std::cout << "      ";
                        std::cout << "<" << depth << ":";
                        for (size_t i = 0; i < inhaltZahl; ++i) {
                            std::cout << "<" << inhalt[i] << ">";
                        }
                        std::cout << ">";
                        std::cout << std::endl;
                    }
                }
			}
			else {
                if (depth <= layer || layer == -1UL) {
                    unterknoten->print(layer,flat);

                    if (!flat) {
                        for (size_t i = 0; i < depth; ++i)
                            std::cout << "      ";
                        std::cout << "**" << depth << "|" << richtung << "**" << std::endl;
                    }

                    unterknoten2->print(layer,flat);
                }
			}
			return;
		}

		bool member(T x, bool printWay) {
			if (isLeaf) {
				for (size_t i = 0; i < inhaltZahl; ++i)
					if (inhalt[i] == x) {
                        if (printWay) std::cout << "((" << inhalt[i] << "))\n";
						return true;
					}
			}
			else {
                if (printWay) std::cout << richtung << " > ";
				if (x < richtung || x == richtung) return unterknoten->member(x,printWay);
				else return unterknoten2->member(x,printWay);
			}
			if (printWay) std::cout << richtung << "*NOT FOUND*" << std::endl;
			return false;
		}

		int remove(T x) {
			if (!isLeaf) {
                int returnWert = -1;
				if (x <= richtung) returnWert = unterknoten->remove(x);
				else returnWert = unterknoten2->remove(x);
                if (returnWert == 2) {//direktes Kind zerfällt
                    isLeaf = true;
                    T* zwischenspeicher;
                    inhalt = new T[MAX_SIZE];
                    if (x <= richtung) {
                        zwischenspeicher = unterknoten2->getInhalt();
                        inhaltZahl = unterknoten2->inhaltZahl;
                    } else {
                        zwischenspeicher = unterknoten->getInhalt();
                        inhaltZahl = unterknoten->inhaltZahl;
                    }
                    for (size_t n = 0; n < inhaltZahl; ++n) {
                        inhalt[n] = zwischenspeicher[n];
                    }
                    delete unterknoten;
                    delete unterknoten2;
                    unterknoten = NULL;
                    unterknoten2 = NULL;
                    return 1;
                } else return returnWert;
			} else {
				if (inhaltZahl==1 && depth > 0) {
                    return 2;
				} else {
                    for (size_t n = 0; n < MAX_SIZE; ++n) {
                        if (inhalt[n] == x) {
                            inhalt[n] = inhalt[inhaltZahl-1];
                            sort();
                            inhaltZahl--;
                            return 1;
                        }
                    }
                    return 0;
				}
			}
		}

		bool nichtVoll() {
			return inhaltZahl < MAX_SIZE+1;
		}

		void setTiefe(size_t tiefe) {
			this->depth = tiefe;
		}
};

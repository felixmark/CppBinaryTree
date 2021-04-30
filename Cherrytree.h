#include "Sakura.h"

template<typename T> class Cherrytree {
	private:
		Sakura<T> *wurzel;
	public:
		Cherrytree() {
			wurzel = new Sakura<T>;
			wurzel->setTiefe(0);
		}
		~Cherrytree() { delete wurzel; }
		bool add(T wert) {
			if (!wurzel->member(wert,false)) {
				wurzel->add(wert);
				return true;
			} else return false;
		}
		bool member(T wert, bool printWay = true) {
			return wurzel->member(wert,printWay);
		}
        size_t count() {
            return wurzel->count(0);
        }
        bool remove(T wert) {
            return wurzel->remove(wert) == 1;
        }
        void print(bool flat) {
			wurzel->print(-1, flat);
		}
		void print(size_t layer = -1, bool flat = false) {
			std::cout << "Cherrytree:" << std::endl;
			std::cout << "________________________________________________________________________________" << std::endl <<std::endl;
			wurzel->print(layer, flat);
		}
};

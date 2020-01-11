#include "cell.h"
#include <iostream>

Cell::Cell(size_t r, size_t c): r{r}, c{c} {
	this->setState({StateType::NewPiece, Colour::NoColour, Direction::N});
}

void Cell::setPiece(Colour colour) {
		this->colour = colour;
}
 
void Cell::toggle() {
	if (colour == Colour::Black) {colour = Colour::White; }
	else { colour = Colour::Black;}
}

Info Cell::getInfo() const {
	Info a;
	a.row = r;
	a.col = c;
	a.colour = colour;
	return a;
}

void Cell::notify(Subject<Info, State> &whoFrom) {
	Info in = whoFrom.getInfo();
	if (colour == Colour::NoColour) { return;}
	else {
      Direction d;
      if (in.row == r) {
      	if (in.col == (c-1)) {
      		d = Direction::W;
      	}
      	else {
      		d = Direction::E;                    
      	}
      }
      else if (in.row == (r-1)) {
          if (in.col == (c-1)) {
          	d = Direction::NW;
          }
          else if (in.col == (c)) {
          	d = Direction::N;
          }
          else if (in.col == (c+1)) {
          	d = Direction::NE;
          }              
        } 
      else if (in.row == (r+1)) {
          if (in.col == (c-1)) {
          	d =Direction::SW;
          }
          else if (in.col == (c)) {
          	d = Direction::S;
          }
          else if (in.col == (c+1)) {
          	d =Direction::SE;
          }              
        }
		if (whoFrom.getState().type == StateType::NewPiece) {
			if (in.colour != colour) {
  			this->setState(State{StateType::Relay, in.colour, d});
  			this->notifyObservers();
			}
			else {}
		}
		else if (whoFrom.getState().type == StateType::Relay) {
			if (whoFrom.getState().direction == d) {
  			if (whoFrom.getState().colour == colour) {
	  			this->setState(State{StateType::Reply, whoFrom.getState().colour, d});
	  			this->notifyObservers();
  			}
  			else {
  				this->setState(State{StateType::Relay, whoFrom.getState().colour, d});
  				this->notifyObservers();
  			}
			}
		}
		else if (whoFrom.getState().type == StateType::Reply) {
			if (d == Direction::NW) { d = Direction::SE; }
			else if (d == Direction::N) { d = Direction::S; 
			}
			else if (d == Direction::NE) { d = Direction::SW; }
			else if (d == Direction::W) { d = Direction::E; }
			else if (d == Direction::E) { d = Direction::W; }
			else if (d == Direction::SW) { d = Direction::NE; }
			else if (d == Direction::S) { d = Direction::N; }
			else if (d == Direction::SE) { d = Direction::NW; }
			if (whoFrom.getState().direction == d) {
  			if (whoFrom.getState().colour == colour) {
  			}
  			else {
  			this->toggle();
  			this->setState(State{StateType::Reply, whoFrom.getState().colour, d});
  			this->notifyObservers();
  			}
			}
		}
	}
} 

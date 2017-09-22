/*
 * ************************************************************************************* SLIM (Stateflow Language IMplementation) *************************************************************************************
 * This library provides a way to define a hierarchical state machine (OR decomposition). A hierarchical state machine is seen as a collection of states, each of which is again a state machine on its own. Moreover,
 * events that are dispatched to a state machine - at whichever level it is - are also dispatched to the currently active state; as the latter is again a state machine, events propagate downwards in the hierarchy.
 * This is exactly how Stateflow manages events, according to a semantic that is the opposite of that adopted by UML. The main advantage is that this solution doesn't need any dynamic binding of methods, because
 * state is not a polymorphic entity anymore.
 * This version is based on the 'double-switch' pattern, turned into a 'triple-switch' one to manage multiple state machines (super-states), and only supports OR decomposition.
 * Author: Alessandro Trifoglio
 */

#include "inc/beh2/SLIM.h"

/* Transition primitive: updates the output, the state and then dispatches the event to the just activated internal state, according to top-down Stateflow semantics */

void tran (State* me, const unsigned int e, State* target, const TransitionMode mode, const Action action) {

	if (mode==EXTERNAL) { 																			/* Exit actions must be performed, starting from the lowest node in the hierarchy */
		State* child = me->state;
		unsigned int i;
		for (i=1; !child->isLeaf; i++) {
			child = child->state;
		}
		for (; i>0; i--) {
			(*child->exitAction)();
			if (child->hasHistory==false) init (child);
			child = child->parent;
		}
	}

	(*action)();

	if (mode==EXTERNAL) {
		me->state = target;
		State* parent = target;																		/* Entry actions must be performed, starting from the highest node in the hierarchy */
		(*parent->entryAction)();
		while (!parent->isLeaf) {
			parent = parent->state;
			(*parent->entryAction)();
		}
	}

	if (mode==INTERNAL) {
		if (!target->isLeaf) dispatch (target, e);
	}
	
}

/* Init primitive */

void init (State* me) {
	if (!me->isLeaf) {
		(*me->action_o)();
		me->state = me->state_o;
	}
}

/* Void action */

void voidAction () {
	;
}

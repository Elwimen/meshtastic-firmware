#pragma once

/**
 * Create module instances here.  If you are adding a new module, you must 'new' it here (or somewhere else)
 */
void setupModules();

/**
 * Ask for module instances to be reconciled against moduleConfig at the next safe point.
 *
 * Called by AdminModule when a module's enabled flag changes, INSTEAD of constructing or
 * destroying anything itself: admin packet handling runs inside MeshModule::callModules(),
 * which iterates the module vector, and MeshModule's destructor erases from that same
 * vector - deleting a module from there invalidates the running iteration.
 */
void requestModuleReconcile();

/**
 * If a reconcile was requested, bring module instances in line with moduleConfig -
 * constructing modules whose enabled flag was switched on and deleting those switched off.
 *
 * Runs from the main loop after service->loop() returns, so no packet dispatch is on the
 * stack. Construction conditions are shared with setupModules() so boot and reconcile
 * cannot drift apart.
 */
void reconcileModules();

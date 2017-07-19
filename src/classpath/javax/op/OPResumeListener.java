package javax.op;

// XXX NVM CHANGE - added

/**
 * This class must be implemented by objects that must re-initialize
 * state upon new executions of an orthogonally persistent JVM.
 * Classes must be registered using OPRuntime.addListener().
 * The resume() method will be invoked during JVM re-initialization.
 */
public interface OPResumeListener {

	/**
         * Method that will be invoked during JVM re-initialization.
	 */
	public void resume();

}

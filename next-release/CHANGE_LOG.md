 * 8.73:
     - Code improvements for speed
       * Using inline for NullWriter
       * Added forceCreation_ param when getting logger internally to allow fast logger access when write log
       * Lock mutex as soon as start enter Writer

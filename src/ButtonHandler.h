class ButtonHandler {
  private:
  /**
   * @brief The currently pressed button or -1 if no button is pressed.
   * 
   */
  static int activeButton;

  /**
   * @brief Called when a button is pressed.
   * 
   */
  static void (*onPressHandler)(int button);

  /**
   * @brief Called when a button is released.
   * 
   */
  static void (*onReleaseHandler)(int button);

  /**
   * @brief Called each loop step that the active button is still down.
   * 
   */
  static void (*whileDownHandler)(int button);

  public:
  /**
   * @brief Updates the handler.
   * 
   * @param currentPressed The currently pressed button or -1 if no button is pressed.
   */
  static void update(int currentPressed);

  /**
   * @brief Attach an observer function to the button press event.
   * 
   * @param onPress The event handler.
   */
  static void registerOnPress(void (*onPress)(int button));

  /**
   * @brief Attach an observer function to the button release event.
   * 
   * @param onRelease The event handler.
   */
  static void registerOnRelease(void (*onRelease)(int button));

  /**
   * @brief Attach an observer function to the button while down event.
   * 
   * @param whileDown The event handler.
   */
  static void registerWhileDown(void (*whileDown)(int button));
};
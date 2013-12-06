<?php
/**
 * @file
 */

/**
 * Missing define in ALMA client.
 */
define('ALMA_SERVICE_METHOD_EMAIL', 'email');
/**
 * SMS Service wrapper.
 *
 * A small wrapper fro missing ALMA functionality.
 */
class Smsservice extends AlmaClient {
  /**
   * Implements to check messages service in patron (not implemented in original alma module only implemented add and remove messages).
   * @param string $borr_card
   *   User CPR.
   * @param string $pin_code
   *   User password.
   * @param bool $extended
   *   Whether to fetch extended user data.
   *
   * @return array
   *   An array with enabled reminder options.
   */
  function GetPatronInfo($borr_card, $pin_code, $extended = FALSE) {
    $path = ($extended) ? 'patron/informationExtended' : 'patron/information';
    $info_node = ($extended) ? 'patronInformationExtended' : 'patronInformation';

    $doc = $this->request($path, array(
      'borrCard' => $borr_card,
      'pinCode' => $pin_code
    ));

    $info = $doc->getElementsByTagName($info_node)->item(0);
    $data = array(
      'sendMethods' => array(),
    );

    // The missing part.
    foreach ($info->getElementsByTagName('sendMethod') as $type) {
      $data['sendMethods'][] = array(
        'value' => $type->getAttribute('value'),
      );
    }

    return $data;
  }
}

<?php
/**
 * @file
 */

/**
 * Missing define in ALMA client.
 */
define('ALMA_SERVICE_METHOD_EMAIL', 'email');
/**
 * Instead of copying alma to sites/all and maintain it,
 *  we defind our own methods to implement missing alma integration.
 */
class Smsservice extends AlmaClient {
  /**
   * Implements to check messages service in patron
   *  (not implemented in original alma module
   *  only implemented add and remove messages).
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

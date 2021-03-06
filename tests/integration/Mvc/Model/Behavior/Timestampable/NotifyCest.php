<?php
declare(strict_types=1);

/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalconphp.com>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */

namespace Phalcon\Test\Integration\Mvc\Model\Behavior\Timestampable;

use IntegrationTester;

/**
 * Class NotifyCest
 */
class NotifyCest
{
    /**
     * Tests Phalcon\Mvc\Model\Behavior\Timestampable :: notify()
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function mvcModelBehaviorTimestampableNotify(IntegrationTester $I)
    {
        $I->wantToTest('Mvc\Model\Behavior\Timestampable - notify()');
        $I->skipTest('Need implementation');
    }
}

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

namespace Phalcon\Test\Unit\Crypt;

use UnitTester;

/**
 * Class SetHashAlgoCest
 */
class SetHashAlgoCest
{
    /**
     * Tests Phalcon\Crypt :: setHashAlgo()
     *
     * @param UnitTester $I
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2019-04-16
     */
    public function cryptSetHashAlgo(UnitTester $I)
    {
        $I->wantToTest('Crypt - setHashAlgo()');

        $I->skipTest('Need implementation');
    }
}
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

namespace Phalcon\Test\Integration\Mvc\Collection;

use IntegrationTester;

/**
 * Class SkipOperationCest
 */
class SkipOperationCest
{
    /**
     * Tests Phalcon\Mvc\Collection :: skipOperation()
     *
     * @param IntegrationTester $I
     * @since  2018-11-13
     * @author Phalcon Team <team@phalconphp.com>
     */
    public function mvcCollectionSkipOperation(IntegrationTester $I)
    {
        $I->wantToTest('Mvc\Collection - skipOperation()');
        $I->skipTest('Need implementation');
    }
}

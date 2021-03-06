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

namespace Phalcon\Test\Unit\Collection;

use Phalcon\Collection;
use UnitTester;

class SetCest
{
    /**
     * Tests Phalcon\Collection :: set()
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function collectionSet(UnitTester $I)
    {
        $I->wantToTest('Collection - set()');

        $collection = new Collection();

        $collection->set('three', 'two');

        $I->assertEquals(
            'two',
            $collection->get('three')
        );

        $collection->three = 'Phalcon';

        $I->assertEquals(
            'Phalcon',
            $collection->get('three')
        );

        $collection->offsetSet('three', 123);

        $I->assertEquals(
            123,
            $collection->get('three')
        );


        $collection['three'] = true;

        $I->assertTrue(
            $collection->get('three')
        );
    }
}

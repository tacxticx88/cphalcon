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

namespace Phalcon\Test\Integration\Forms\Element\Email;

use IntegrationTester;
use Phalcon\Forms\Element\Email;
use Phalcon\Test\Fixtures\Traits\DiTrait;

class GetSetNameCest
{
    use DiTrait;

    public function _before(IntegrationTester $I)
    {
        $this->newDi();
        $this->setDiEscaper();
        $this->setDiUrl();
    }

    /**
     * Tests Phalcon\Forms\Element\Email :: getName() / setName()
     *
     * @author Sid Roberts <https://github.com/SidRoberts>
     * @since  2019-06-02
     */
    public function formsElementEmailGetSetName(IntegrationTester $I)
    {
        $I->wantToTest('Forms\Element\Email - getName() / setName()');

        $element = new Email('simple');

        $I->assertEquals(
            'simple',
            $element->getName()
        );

        $element->setName('different');

        $I->assertEquals(
            'different',
            $element->getName()
        );
    }
}

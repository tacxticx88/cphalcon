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
use MongoDB\Database;
use Phalcon\Test\Fixtures\Mvc\Collections\Robots;
use Phalcon\Test\Fixtures\Traits\DiTrait;

/**
 * Class CreateIfNotExistCest
 */
class CreateIfNotExistCest
{
    use DiTrait;

    private $source;

    /** @var Database $mongo */
    private $mongo;

    public function _before()
    {
        $this->setNewFactoryDefault();
        $this->setDiCollectionManager();
        $this->setDiMongo();

        $this->source = (new Robots)->getSource();
        $this->mongo = $this->getDi()->get('mongo');

        $this->mongo->selectCollection($this->source)->insertOne(
            [
                'first_name' => 'Unknown',
                'last_name' => 'Nobody',
            ]
        );
    }

    /**
     * Tests Phalcon\Mvc\Collection :: createIfNotExist()
     *
     * @param IntegrationTester $I
     * @since  2018-11-13
     * @author Phalcon Team <team@phalconphp.com>
     */
    public function mvcCollectionCreateIfNotExist(IntegrationTester $I)
    {
        $I->wantToTest('Mvc\Collection - createIfNotExist()');

        $robot = new Robots;
        $robot->first_name = 'I';
        $robot->last_name = 'Robot';

//        $state = $robot->createIfNotExist(
//            [
//                'first_name' => 'Unknown'
//            ]
//        );

        // TODO corrections

        $I->skipTest('Need implementation');
    }

    public function _after()
    {
        $this->mongo->dropCollection($this->source);
    }
}

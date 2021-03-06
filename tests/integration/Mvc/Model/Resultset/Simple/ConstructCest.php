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

namespace Phalcon\Test\Integration\Mvc\Model\Resultset\Simple;

use function cacheModelsDir;
use IntegrationTester;
use Phalcon\Helper\Str;
use Phalcon\Mvc\Model\Resultset\Simple;
use Phalcon\Test\Fixtures\Traits\DiTrait;
use Phalcon\Test\Models\Robots;

/**
 * Class ConstructCest
 */
class ConstructCest
{
    use DiTrait;


    public function _before(IntegrationTester $I)
    {
        $this->setNewFactoryDefault();
        $this->setDiMysql();
        $I->cleanDir(cacheModelsDir());
    }

    /**
     * Tests Phalcon\Mvc\Model\Resultset\Simple :: __construct()
     * Work with Simple Resultset by load data from the file cache (complete
     * PHQL option).
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2019-04-27
     */
    public function mvcModelResultsetSimpleConstructCompletePhql(IntegrationTester $I)
    {
        $I->wantToTest('Mvc\Model\Resultset\Simple - __construct() - complete PHQL');

        $cache    = $this->getAndSetModelsCacheStream();
        $manager  = $this->getService('modelsManager');
        $filePath = cacheModelsDir()
            . 'phstrm-/'
            . Str::dirFromFile('test-resultset');

        $robots = $manager->executeQuery('SELECT * FROM ' . Robots::class);

        $I->assertInstanceOf(Simple::class, $robots);

        $I->assertCount(6, $robots);
        $I->assertEquals($robots->count(), 6);

        $cache->set('test-resultset', $robots);

        $I->seeFileFound('test-resultset', $filePath);

        $robots = $cache->get('test-resultset');

        $I->assertInstanceOf(Simple::class, $robots);
        $I->assertCount(6, $robots);
        $I->assertEquals($robots->count(), 6);

        $result = $cache->clear();
        $I->assertTrue($result);

        $I->amInPath(cacheModelsDir());
        $I->dontSeeFileFound('test-resultset', $filePath);
    }

    /**
     * Tests Phalcon\Mvc\Model\Resultset\Simple :: __construct()
     * Work with Simple Resultset by load data from the file cache (incomplete
     * PHQL option).
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2019-04-27
     */
    public function mvcModelResultsetSimpleConstructIncompletePhql(IntegrationTester $I)
    {
        $I->wantToTest('Mvc\Model\Resultset\Simple - __construct() - incomplete PHQL');

        $cache    = $this->getAndSetModelsCacheStream();
        $manager  = $this->getService('modelsManager');
        $filePath = cacheModelsDir()
            . 'phstrm-/'
            . Str::dirFromFile('test-resultset');

        $robots = $manager->executeQuery('SELECT id FROM ' . Robots::class);

        $I->assertInstanceOf(Simple::class, $robots);
        $I->assertCount(6, $robots);
        $I->assertEquals($robots->count(), 6);

        $cache->set('test-resultset', $robots);

        $I->seeFileFound('test-resultset', $filePath);

        $robots = $cache->get('test-resultset');

        $I->assertInstanceOf(Simple::class, $robots);
        $I->assertCount(6, $robots);
        $I->assertEquals($robots->count(), 6);

        $cache->delete('test-resultset');

        $I->dontSeeFileFound('test-resultset', $filePath);
    }
}

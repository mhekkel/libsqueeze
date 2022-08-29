//          Copyright Maarten L. Hekkelman, 2022
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE Squeeze_Test
#include <boost/test/included/unit_test.hpp>

#include <squeeze.hpp>

BOOST_AUTO_TEST_CASE(test_1)
{
    std::vector<uint32_t> t1{ 1, 2, 3, 3, 2, 1 };

    std::vector<uint8_t> bits;
    sq::obitstream obs(bits);

    sq::write_delta_array(obs, t1);
    obs.sync();

    sq::ibitstream ibs(obs);
    auto t2 = sq::read_delta_array(ibs);

    BOOST_TEST(t1 == t2);
}

BOOST_AUTO_TEST_CASE(test_2)
{
    std::vector<uint32_t> t1{ 3, 2, 1, 0 };

    std::vector<uint8_t> bits;
    sq::obitstream obs(bits);

    sq::write_delta_array(obs, t1);
    obs.sync();

    sq::ibitstream ibs(obs);
    auto t2 = sq::read_delta_array(ibs);

    BOOST_TEST(t1 == t2);
}

BOOST_AUTO_TEST_CASE(test_3)
{
    std::vector<uint32_t> t1{ 0, 1, 2, 3 };

    std::vector<uint8_t> bits;
    sq::obitstream obs(bits);

    sq::write_delta_array(obs, t1);
    obs.sync();

    sq::ibitstream ibs(obs);
    auto t2 = sq::read_delta_array(ibs);

    BOOST_TEST(t1 == t2);
}


BOOST_AUTO_TEST_CASE(test_4)
{
    std::vector<uint32_t> t1{ 3, 0, 0, 3 };

    std::vector<uint8_t> bits;
    sq::obitstream obs(bits);

    sq::write_delta_array(obs, t1);
    obs.sync();

    sq::ibitstream ibs(obs);
    auto t2 = sq::read_delta_array(ibs);

    BOOST_TEST(t1 == t2);
}


// BOOST_AUTO_TEST_CASE(test_5)
// {
//     std::vector<uint32_t> t1{ 0, 1, 2, 3 };

//     std::vector<uint8_t> bits;
//     sq::obitstream obs(bits);

//     BOOST_CHECK_THROW(sq::write_array(obs, t1), boost::execution_exception);
// }

BOOST_AUTO_TEST_CASE(test_6)
{
    std::vector<uint32_t> t1{ 1, 2, 3, 4, 5 };

    std::vector<uint8_t> bits;
    sq::obitstream obs(bits);

    sq::write_array(obs, t1);
    obs.sync();

    sq::ibitstream ibs(obs);
    auto t2 = sq::read_array(ibs);

    BOOST_TEST(t1 == t2);
}

BOOST_AUTO_TEST_CASE(test_7)
{
    std::vector<uint32_t> t1{ 0, 2, 4, 10, 11, 125, 32767, 32768, 32769 };

    std::vector<uint8_t> bits;
    sq::obitstream obs(bits);

    sq::write_array(obs, t1);
    obs.sync();

    sq::ibitstream ibs(obs);
    auto t2 = sq::read_array(ibs);

    BOOST_TEST(t1 == t2);
}
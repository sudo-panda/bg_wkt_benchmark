#define CELERO_STATIC
#include <iostream>
#include <random>
#include <celero/Celero.h>
#include <write.hpp>
#include <cmath>
#include <boost/geometry/geometry.hpp>

namespace bg = boost::geometry;

struct Fixture : celero::TestFixture {
 public:
  typedef bg::model::d2::point_xy<double> point_t;
  boost::geometry::model::multi_point<point_t> more_sig_data_;
  boost::geometry::model::multi_point<point_t> less_sig_data_;

  Fixture() = default;

  std::vector<celero::TestFixture::ExperimentValue> getExperimentValues() const override {
    std::vector<celero::TestFixture::ExperimentValue> v;
    std::size_t size = 5;
    for (std::size_t i = 0; i < size; i++) {
      v.emplace_back(static_cast<int64_t>(pow(10, i)), 0);
    }

    return v;
  };

  void setUp(const celero::TestFixture::ExperimentValue &x) override {
    std::random_device rand_dev;
    std::uniform_real_distribution<double> uni_real_dist(-100.0, 100.0);
    std::uniform_int_distribution<int> uni_int_dist(-10000, 10000);

    auto const size = static_cast<std::size_t>(x.Value);
    for (std::size_t i = 0; i < size; i++) {
      bg::append(more_sig_data_,
                 bg::make<point_t>(
                     uni_real_dist(rand_dev),
                     uni_real_dist(rand_dev)
                 ));
      bg::append(less_sig_data_,
                 bg::make<point_t>(
                     uni_int_dist(rand_dev) / 1000.0,
                     uni_int_dist(rand_dev) / 1000.0
                 ));
    }
  }

  void tearDown() override {
    less_sig_data_ = {};
    more_sig_data_ = {};
  }
};

CELERO_MAIN

// Bselining to_string method

BASELINE_F(wkt_more_sig, to_string, Fixture, 0, 100) {
  std::stringstream ss;
  celero::DoNotOptimizeAway(ss<<bg::to_string::wkt(this->more_sig_data_));
  ss.str();
}

BASELINE_F(wkt_less_sig, to_string, Fixture, 0, 100) {
  std::stringstream ss;
  celero::DoNotOptimizeAway(ss<<bg::to_string::wkt(this->less_sig_data_));
  celero::DoNotOptimizeAway(ss.str());
}

BASELINE_F(to_wkt_more_sig, to_string, Fixture, 0, 100) {
  celero::DoNotOptimizeAway(bg::to_string::to_wkt(this->more_sig_data_));
}

BASELINE_F(to_wkt_less_sig, to_string, Fixture, 0, 100) {
  celero::DoNotOptimizeAway(bg::to_string::to_wkt(this->less_sig_data_));
}

// Benchmarking lexical_cast method

BENCHMARK_F(wkt_more_sig, lexical_cast, Fixture, 0, 100) {
  std::stringstream ss;
  celero::DoNotOptimizeAway(ss<<bg::lexical_cast::wkt(this->more_sig_data_));
  celero::DoNotOptimizeAway(ss.str());
}

BENCHMARK_F(wkt_less_sig, lexical_cast, Fixture, 0, 100) {
  std::stringstream ss;
  celero::DoNotOptimizeAway(ss<<bg::lexical_cast::wkt(this->less_sig_data_));
  celero::DoNotOptimizeAway(ss.str());
}

BENCHMARK_F(to_wkt_more_sig, lexical_cast, Fixture, 0, 100) {
  celero::DoNotOptimizeAway(bg::lexical_cast::to_wkt(this->more_sig_data_));
}

BENCHMARK_F(to_wkt_less_sig, lexical_cast, Fixture, 0, 100) {
  celero::DoNotOptimizeAway(bg::lexical_cast::to_wkt(this->less_sig_data_));
}


// Benchmarking stringstream with precision set method

BENCHMARK_F(wkt_more_sig, ss_w_precision, Fixture, 0, 100) {
  std::stringstream ss;
  celero::DoNotOptimizeAway(ss<<bg::ss_w_precision::wkt(this->more_sig_data_));
  celero::DoNotOptimizeAway(ss.str());
}

BENCHMARK_F(wkt_less_sig, ss_w_precision, Fixture, 0, 100) {
  std::stringstream ss;
  celero::DoNotOptimizeAway(ss<<bg::ss_w_precision::wkt(this->less_sig_data_));
  celero::DoNotOptimizeAway(ss.str());
}

BENCHMARK_F(to_wkt_more_sig, ss_w_precision, Fixture, 0, 100) {
  celero::DoNotOptimizeAway(bg::ss_w_precision::to_wkt(this->more_sig_data_));
}

BENCHMARK_F(to_wkt_less_sig, ss_w_precision, Fixture, 0, 100) {
  bg::ss_w_precision::to_wkt(this->less_sig_data_);
}

// Benchmarking stringstream without precision set method

BENCHMARK_F(wkt_more_sig, ss_wo_precision, Fixture, 0, 100) {
  std::stringstream ss;
  celero::DoNotOptimizeAway(ss<<bg::ss_wo_precision::wkt(this->more_sig_data_));
  celero::DoNotOptimizeAway(ss.str());
}

BENCHMARK_F(wkt_less_sig, ss_wo_precision, Fixture, 0, 100) {
  std::stringstream ss;
  celero::DoNotOptimizeAway(ss<<bg::ss_wo_precision::wkt(this->less_sig_data_));
  celero::DoNotOptimizeAway(ss.str());
}

BENCHMARK_F(to_wkt_more_sig, ss_wo_precision, Fixture, 0, 100) {
  celero::DoNotOptimizeAway(bg::ss_wo_precision::to_wkt(this->more_sig_data_));
}

BENCHMARK_F(to_wkt_less_sig, ss_wo_precision, Fixture, 0, 100) {
  celero::DoNotOptimizeAway(bg::ss_wo_precision::to_wkt(this->less_sig_data_));
}
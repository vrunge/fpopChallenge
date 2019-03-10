// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// fpopChallenge
List fpopChallenge(Rcpp::NumericVector vectData, Rcpp::NumericVector vectWeight, double penalty);
RcppExport SEXP _fpopChallenge_fpopChallenge(SEXP vectDataSEXP, SEXP vectWeightSEXP, SEXP penaltySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type vectData(vectDataSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type vectWeight(vectWeightSEXP);
    Rcpp::traits::input_parameter< double >::type penalty(penaltySEXP);
    rcpp_result_gen = Rcpp::wrap(fpopChallenge(vectData, vectWeight, penalty));
    return rcpp_result_gen;
END_RCPP
}
// fpopRunge
List fpopRunge(Rcpp::NumericVector vectData, Rcpp::NumericVector vectWeight, double penalty);
RcppExport SEXP _fpopChallenge_fpopRunge(SEXP vectDataSEXP, SEXP vectWeightSEXP, SEXP penaltySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type vectData(vectDataSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type vectWeight(vectWeightSEXP);
    Rcpp::traits::input_parameter< double >::type penalty(penaltySEXP);
    rcpp_result_gen = Rcpp::wrap(fpopRunge(vectData, vectWeight, penalty));
    return rcpp_result_gen;
END_RCPP
}
// fpopRomano
List fpopRomano(std::vector<double> vectData, double penalty);
RcppExport SEXP _fpopChallenge_fpopRomano(SEXP vectDataSEXP, SEXP penaltySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double> >::type vectData(vectDataSEXP);
    Rcpp::traits::input_parameter< double >::type penalty(penaltySEXP);
    rcpp_result_gen = Rcpp::wrap(fpopRomano(vectData, penalty));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_fpopChallenge_fpopChallenge", (DL_FUNC) &_fpopChallenge_fpopChallenge, 3},
    {"_fpopChallenge_fpopRunge", (DL_FUNC) &_fpopChallenge_fpopRunge, 3},
    {"_fpopChallenge_fpopRomano", (DL_FUNC) &_fpopChallenge_fpopRomano, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_fpopChallenge(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}

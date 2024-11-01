// navigator.privateAttribution.delegateBudgetToAdTech({
//   adTechIdentifier: "adtech1.example",
//   requestedEpsilon: 1.5,
//   validationToken: "token_exaple",
//   onSuccess: (response) => {
//     console.log(`Success`);
//     let delegation_object = response.delegation_object;
//     let report1 = delegation_object.requestOptimizationReport({
//       aggregator: "aggregator-1.example",
//       histogramSize: 3, //histogram contribution 3 wide
//       desiredEpsilon: 0.5,
//       onSuccess: (report) => {
//         console.log("Report  adtech1.example:", report);
//       },
//       onFailure: (error) => {
//         console.error(
//           "API2 report request for adtech1.example failed:",
//           error.message
//         );
//       },
//     });
//   },
//   onFailure: (error) => {
//     console.error(`Failed to delegate budget`);
//   },
// });

// //Ad-tech utilising the budget

// let report1 = delegation_object.requestOptimizationReport({
//   aggregator: "aggregator-1.example",
//   histogramSize: 3,
//   desiredEpsilon: 0.5,
//   onSuccess: (report) => {
//     console.log("Received report:", report);
//   },
//   onFailure: (error) => {
//     console.error("API2 report request failure");
//   },
// });

// ad-tech example, and requested epsilon, this is an example usage assuming one first party and three asosciated ad-techs
let adTechIdentifier = "adtech1.example";
let desiredEpsilon = 1.5;
let totalAvailableBudget = 3.0;
let associatedAdTechs = [
  "adtech1.example",
  "adtech2.example",
  "adtech3.example",
];

// split the budget for fair-share and extra delegation
let fairShareBudget = totalAvailableBudget * 0.5; //the 0.5 factor can change, depending on what we decide
let extraBudget = totalAvailableBudget - fairShareBudget;
let fairSharePerAdTech = fairShareBudget / associatedAdTechs.length; //per ad-tech
function getAdTechAcquiredBudget(adTechIdentifier) {
  let acquiredBudgets = {
    "adtech1.example": 0.5,
    "adtech2.example": 0.2,
    "adtech3.example": 0.3,
  };
  return acquiredBudgets[adTechIdentifier] || 0; //budgets from this party
}
// ad-techs remaining virtual budgets
function getAdTechVirtualBudgetLeft(adTechIdentifier) {
  let virtualBudgetsLeft = {
    "adtech1.example": 1.0,
    "adtech2.example": 0.8,
    "adtech3.example": 0.6,
  };
  return virtualBudgetsLeft[adTechIdentifier] || 0;
}

function delegateBudgetToAdTech(adTechIdentifier, desiredEpsilon) {
  let acquiredBudget = getAdTechAcquiredBudget(adTechIdentifier);
  let virtualBudgetLeft = getAdTechVirtualBudgetLeft(adTechIdentifier);
  let maxAllocatableEpsilon = fairSharePerAdTech + extraBudget;

  // delegate the adjusted budget
  let proportionAcquired = acquiredBudget / totalAvailableBudget;
  let allocationFactor = 1 - proportionAcquired;
  // possible bidget authorised, the maximum possible times the allocation factor which is inversely proportional to the already acquired budget
  let possibleEpsilon = maxAllocatableEpsilon * allocationFactor;
  possibleEpsilon = Math.min(possibleEpsilon, virtualBudgetLeft);
  //result can be the minimum between the desired and the possible values
  let allocatedEpsilon = Math.min(desiredEpsilon, possibleEpsilon);

  // check if the first party has enough budget
  if (allocatedEpsilon > 0 && allocatedEpsilon <= totalAvailableBudget) {
    totalAvailableBudget -= allocatedEpsilon;
    // also update the ad-tech's virtual budget
    let delegation_object = {
      adTechIdentifier: adTechIdentifier,
      allocatedEpsilon: allocatedEpsilon,
      requestOptimizationReport: function (params) {
        if (params.desiredEpsilon <= this.allocatedEpsilon) {
          console.log(`Ad-tech received report`);
          // also reduce allocatedEpsilon
        } else {
          console.error(`Ad-tech  requested epsilon exceeds delegated budget`);
        }
      },
    };

    //use by the adtech
    delegation_object.requestOptimizationReport({
      aggregator: "aggregator-1.example",
      histogramSize: 3, // histogram 3 wide
      desiredEpsilon: 0.5,
    });
  } else {
    console.error(`Failed to delegate budget`);
  }
}
//budget from first party to third party
delegateBudgetToAdTech(adTechIdentifier, desiredEpsilon);

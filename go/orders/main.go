package main

// To execute Go code, please declare a func main() in a package "main"

/*

  You own an online business that has recently run some promotions with multiple marketing partners,
   which drive traffic to your website via ads.

  We want to process a data feed consisting of ad visits and orders, we need to determine how much to pay our partners.

  We only pay out a partner if they drove at least 5,000 visits, and if they meet this minimum - we pay a 10% commission
   on all orders that resulted from visits driven by that particular partner.

  Implement a function that takes a list of vists and a list of orders which returns the total commission amount we owe to each partner.

*/

/*
	Visits and Orders have the following properties:

	Visit
	--------
	visitId
	partnerId

	Order
	--------
	visitId
	amount

	- There can be multiple orders associated with a single visit.  visits:orders => 1:many)
	- Visits and Orders are both unordered lists.
	- Implement a function that returns the total commission amount we owe to each partner.
*/

import "fmt"

type Visit struct {
	VisitID   string
	PartnerID string
}

type Order struct {
	VisitID string
	Amount  int // cents
}

func main() {
	visit := []Visit{}

	for i := range 5000 {
		visit = append(visit, Visit{
			VisitID: "visit-" + fmt.Sprintf("%d", i), PartnerID: "partner-1",
		})
	}

	visit = append(visit, Visit{
		VisitID: "visit-5010", PartnerID: "partner-2",
	})

	order := []Order{
		{VisitID: "visit-1", Amount: 1050},
		{VisitID: "visit-2", Amount: 500},
	}

	commissions := CommissionOwedPerPartner(visit, order)
	for i := range commissions {
		fmt.Printf("PartnerID: %s, commission: %.2f\n", i, float64(commissions[i])/100)
	}
}

func CommissionOwedPerPartner(visit []Visit, order []Order) map[string]int {
	partnerVisit := map[string]int{}
	visitMap := map[string]string{}
	commissions := map[string]int{}
	orders := map[string]int{}

	if len(visit) < 1 || len(order) < 1 {
		return nil
	}
	for v := range visit {
		partnerVisit[visit[v].PartnerID]++
		visitMap[visit[v].VisitID] = visit[v].PartnerID
	}
	for o := range order {
		partnerId, ok := visitMap[order[o].VisitID]
		if ok {
			orders[partnerId] += order[o].Amount
			if partnerVisit[partnerId] >= 5000 {
				total := float64(orders[partnerId]) / 100 * .1
				commissions[partnerId] = int(total * 100)
			}
		}
	}
	return commissions
}
